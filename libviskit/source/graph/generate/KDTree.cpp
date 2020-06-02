#include "graph/generate/KDTree.h"

namespace ivhd::graph::generate
{
	KDTree::Node* KDTree::deepcopyTree(Node* root) {
		if (root == nullptr) return nullptr;
		Node* newRoot = new Node(*root);
		newRoot->left = deepcopyTree(root->left);
		newRoot->right = deepcopyTree(root->right);
		return newRoot;
	}

	KDTree::Node* KDTree::buildTree(std::vector<std::pair<DataPoint, size_t>>::iterator start,
		std::vector<std::pair<DataPoint, size_t>>::iterator end, int currLevel) const
	{
		if (start >= end) return nullptr; // empty tree

		int axis = currLevel % m_sizePoints; // the axis to split on
		auto cmp = [axis](const std::pair<DataPoint, size_t>& p1, const std::pair<DataPoint, size_t>& p2) {
			return p1.first[axis] < p2.first[axis];
		};
		std::size_t len = end - start;
		auto mid = start + len / 2;
		std::nth_element(start, mid, end, cmp); // linear time partition

		// move left (if needed) so that all the equal points are to the right
		// The tree will still be balanced as long as there aren't many points that are equal along each axis
		while (mid > start && (mid - 1)->first[axis] == mid->first[axis]) {
			--mid;
		}

		Node* newNode = new Node(mid->first, currLevel, mid->second);
		newNode->left = buildTree(start, mid, currLevel + 1);
		newNode->right = buildTree(mid + 1, end, currLevel + 1);
		return newNode;
	}

	KDTree::KDTree(std::vector<std::pair<DataPoint, size_t>>& points, size_t dim)
	{
		m_root = buildTree(points.begin(), points.end(), 0);
		m_size = points.size();
		m_sizePoints = dim;
	}

	KDTree::KDTree(const KDTree& rhs)
	{
		m_root = deepcopyTree(rhs.m_root);
		m_size = rhs.m_size;
	}

	KDTree& KDTree::operator=(const KDTree& rhs)
	{
		if (this != &rhs) { // make sure we don't self-assign
			freeResource(m_root);
			m_root = deepcopyTree(rhs.m_root);
			m_size = rhs.m_size;
		}
		return *this;
	}

	void KDTree::freeResource(Node* currNode)
	{
		if (currNode == nullptr) return;
		freeResource(currNode->left);
		freeResource(currNode->right);
		delete currNode;
	}

	KDTree::~KDTree()
	{
		freeResource(m_root);
	}

	std::size_t KDTree::dimension() const
	{
		return m_sizePoints;
	}

	std::size_t KDTree::size() const
	{
		return m_size;
	}

	bool KDTree::empty() const
	{
		return m_size == 0;
	}

	KDTree::Node* KDTree::findNode(Node* currNode, const DataPoint& pt) const
	{
		if (currNode == nullptr || currNode->point == pt) return currNode;

		const auto& currPoint = currNode->point;
		const auto currLevel = currNode->level;
		if (pt[currLevel % m_sizePoints] < currPoint[currLevel % m_sizePoints]) { // recurse to the left side
			return currNode->left == nullptr ? currNode : findNode(currNode->left, pt);
		}
		else { // recurse to the right side
			return currNode->right == nullptr ? currNode : findNode(currNode->right, pt);
		}
	}

	bool KDTree::contains(const DataPoint& pt) const
	{
		const auto node = findNode(m_root, pt);
		return node != nullptr && node->point == pt;
	}

	void KDTree::insert(const DataPoint& pt, const size_t& value)
	{
		auto targetNode = findNode(m_root, pt);
		if (targetNode == nullptr)  // this means the tree is empty
		{
			m_root = new Node(pt, 0, value);
			m_size = 1;
		}
		else {
			if (targetNode->point == pt)  // pt is already in the tree, simply update its value
			{
				targetNode->value = value;
			}
			else  // construct a new node and insert it to the right place (child of targetNode)
			{
				const auto currLevel = targetNode->level;
				Node* newNode = new Node(pt, currLevel + 1, value);
				if (pt[currLevel % m_sizePoints] < targetNode->point[currLevel % m_sizePoints])
				{
					targetNode->left = newNode;
				}
				else
				{
					targetNode->right = newNode;
				}
				++m_size;
			}
		}
	}

	const size_t& KDTree::at(const DataPoint& pt) const
	{
		const auto node = findNode(m_root, pt);
		if (node == nullptr || node->point != pt)
		{
			throw std::out_of_range("Point not found in the KD-Tree");
		}
		else
		{
			return node->value;
		}
	}

	size_t& KDTree::at(const DataPoint& pt)
	{
		const KDTree& constThis = *this;
		return const_cast<size_t&>(constThis.at(pt));
	}

	size_t& KDTree::operator[](const DataPoint& pt)
	{
		auto node = findNode(m_root, pt);
		if (node != nullptr && node->point == pt) // pt is already in the tree
		{
			return node->value;
		}

		// insert pt with default size_t value, and return reference to the new size_t
		insert(pt);
		if (node == nullptr)  // the new node is the root
		{
			return m_root->value;
		}
		return (node->left != nullptr && node->left->point == pt) ? node->left->value : node->right->value;
	}

	void KDTree::nearestNeighborRecurse(const Node* currNode, const DataPoint& key, BoundedPQueue& pQueue) const
	{
		if (currNode == nullptr) return;
		const auto& currPoint = currNode->point;

		// Add the current point to the BPQ if it is closer to 'key' that some point in the BPQ
		// and point is not the same
		if (currPoint.getId() != key.getId())
		{
			pQueue.enqueuePoint(currNode->point, Distance(currPoint, key));
		}

		// Recursively search the half of the tree that contains Point 'key'
		const auto currLevel = currNode->level;
		bool isLeftTree;
		if (key[currLevel % m_sizePoints] < currPoint[currLevel % m_sizePoints])
		{
			nearestNeighborRecurse(currNode->left, key, pQueue);
			isLeftTree = true;
		}
		else {
			nearestNeighborRecurse(currNode->right, key, pQueue);
			isLeftTree = false;
		}

		if (pQueue.size() < pQueue.maxSize() || fabs(key[currLevel % m_sizePoints] - currPoint[currLevel % m_sizePoints]) < pQueue.worst())
		{
			// Recursively search the other half of the tree if necessary
			if (isLeftTree) nearestNeighborRecurse(currNode->right, key, pQueue);
			else nearestNeighborRecurse(currNode->left, key, pQueue);
		}
	}

	std::vector<std::pair<float, DataPoint>> KDTree::kNN(const DataPoint& key, std::size_t k) const
	{
		BoundedPQueue pQueue(k);
		if (empty()) return std::vector<std::pair<float, DataPoint>>{};

		nearestNeighborRecurse(m_root, key, pQueue);

		std::vector<std::pair<float, DataPoint>> result;
		while (!pQueue.emptyPoints()) {
			result.push_back(pQueue.dequeuePoint());
		}

		return result;
	}
}
