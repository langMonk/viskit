#include "graph/KDTree.h"

namespace ivhd::graph
{ 
	typename KDTree::Node* KDTree::deepcopyTree(typename KDTree::Node* root) {
		if (root == NULL) return NULL;
		Node* newRoot = new Node(*root);
		newRoot->left = deepcopyTree(root->left);
		newRoot->right = deepcopyTree(root->right);
		return newRoot;
	}

	typename KDTree::Node* KDTree::buildTree(typename std::vector<std::pair<Point, size_t>>::iterator start,
		typename std::vector<std::pair<Point, size_t>>::iterator end, int currLevel) {
		if (start >= end) return NULL; // empty tree

		int axis = currLevel % m_sizePoints; // the axis to split on
		auto cmp = [axis](const std::pair<Point, size_t>& p1, const std::pair<Point, size_t>& p2) {
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

	KDTree::KDTree(std::vector<std::pair<Point, size_t>>& points, size_t dim) {
		m_root = buildTree(points.begin(), points.end(), 0);
		m_size = points.size();
		m_sizePoints = dim;
	}

	KDTree::KDTree(const KDTree& rhs) {
		m_root = deepcopyTree(rhs.m_root);
		m_size = rhs.m_size;
	}

	KDTree& KDTree::operator=(const KDTree& rhs) {
		if (this != &rhs) { // make sure we don't self-assign
			freeResource(m_root);
			m_root = deepcopyTree(rhs.m_root);
			m_size = rhs.m_size;
		}
		return *this;
	}

	void KDTree::freeResource(typename KDTree::Node* currNode) {
		if (currNode == NULL) return;
		freeResource(currNode->left);
		freeResource(currNode->right);
		delete currNode;
	}

	KDTree::~KDTree() {
		freeResource(m_root);
	}

	std::size_t KDTree::dimension() const {
		return m_sizePoints;
	}

	std::size_t KDTree::size() const {
		return m_size;
	}

	bool KDTree::empty() const {
		return m_size == 0;
	}

	typename KDTree::Node* KDTree::findNode(typename KDTree::Node* currNode, const Point& pt) const {
		if (currNode == NULL || currNode->point == pt) return currNode;

		const Point& currPoint = currNode->point;
		int currLevel = currNode->level;
		if (pt[currLevel % m_sizePoints] < currPoint[currLevel % m_sizePoints]) { // recurse to the left side
			return currNode->left == NULL ? currNode : findNode(currNode->left, pt);
		}
		else { // recurse to the right side
			return currNode->right == NULL ? currNode : findNode(currNode->right, pt);
		}
	}

	bool KDTree::contains(const Point& pt) const {
		auto node = findNode(m_root, pt);
		return node != NULL && node->point == pt;
	}

	void KDTree::insert(const Point& pt, const size_t& value) {
		auto targetNode = findNode(m_root, pt);
		if (targetNode == NULL) { // this means the tree is empty
			m_root = new Node(pt, 0, value);
			m_size = 1;
		}
		else {
			if (targetNode->point == pt) { // pt is already in the tree, simply update its value
				targetNode->value = value;
			}
			else { // construct a new node and insert it to the right place (child of targetNode)
				int currLevel = targetNode->level;
				Node* newNode = new Node(pt, currLevel + 1, value);
				if (pt[currLevel % m_sizePoints] < targetNode->point[currLevel % m_sizePoints]) {
					targetNode->left = newNode;
				}
				else {
					targetNode->right = newNode;
				}
				++m_size;
			}
		}
	}

	const size_t& KDTree::at(const Point& pt) const {
		auto node = findNode(m_root, pt);
		if (node == NULL || node->point != pt) {
			throw std::out_of_range("Point not found in the KD-Tree");
		}
		else {
			return node->value;
		}
	}

	size_t& KDTree::at(const Point& pt) {
		const KDTree& constThis = *this;
		return const_cast<size_t&>(constThis.at(pt));
	}

	size_t& KDTree::operator[](const Point& pt) {
		auto node = findNode(m_root, pt);
		if (node != NULL && node->point == pt) { // pt is already in the tree
			return node->value;
		}
		else { // insert pt with default size_t value, and return reference to the new size_t
			insert(pt);
			if (node == NULL) return m_root->value; // the new node is the root
			else return (node->left != NULL && node->left->point == pt) ? node->left->value : node->right->value;
		}
	}

	void KDTree::nearestNeighborValueRecurse(const typename KDTree::Node* currNode, const Point& key, BoundedPQueue& pQueue) const 
	{
		if (currNode == NULL) return;
		const Point& currPoint = currNode->point;

		// Add the current point to the BPQ if it is closer to 'key' that some point in the BPQ
		pQueue.enqueue(currNode->value, Distance(currPoint, key));

		// Recursively search the half of the tree that contains Point 'key'
		int currLevel = currNode->level;
		bool isLeftTree;
		if (key[currLevel % m_sizePoints] < currPoint[currLevel % m_sizePoints]) {
			nearestNeighborRecurse(currNode->left, key, pQueue);
			isLeftTree = true;
		}
		else {
			nearestNeighborRecurse(currNode->right, key, pQueue);
			isLeftTree = false;
		}

		if (pQueue.size() < pQueue.maxSize() || fabs(key[currLevel % m_sizePoints] - currPoint[currLevel % m_sizePoints]) < pQueue.worst()) {
			// Recursively search the other half of the tree if necessary
			if (isLeftTree) nearestNeighborRecurse(currNode->right, key, pQueue);
			else nearestNeighborRecurse(currNode->left, key, pQueue);
		}
	}

	void KDTree::nearestNeighborRecurse(const typename KDTree::Node* currNode, const Point& key, BoundedPQueue& pQueue) const
	{
		if (currNode == NULL) return;
		const Point& currPoint = currNode->point;

		// Add the current point to the BPQ if it is closer to 'key' that some point in the BPQ
		// and point is not the same
		if (currPoint.getId() != key.getId())
		{
			pQueue.enqueuePoint(currNode->point, Distance(currPoint, key));
		}
		
		// Recursively search the half of the tree that contains Point 'key'
		int currLevel = currNode->level;
		bool isLeftTree;
		if (key[currLevel % m_sizePoints] < currPoint[currLevel % m_sizePoints]) {
			nearestNeighborRecurse(currNode->left, key, pQueue);
			isLeftTree = true;
		}
		else {
			nearestNeighborRecurse(currNode->right, key, pQueue);
			isLeftTree = false;
		}

		if (pQueue.size() < pQueue.maxSize() || fabs(key[currLevel % m_sizePoints] - currPoint[currLevel % m_sizePoints]) < pQueue.worst()) {
			// Recursively search the other half of the tree if necessary
			if (isLeftTree) nearestNeighborRecurse(currNode->right, key, pQueue);
			else nearestNeighborRecurse(currNode->left, key, pQueue);
		}
	}

	size_t KDTree::kNNValue(const Point& key, std::size_t k) const 
	{
		BoundedPQueue pQueue(k); // BPQ with maximum size k
		if (empty()) return size_t(); // default return value if KD-tree is empty

		// Recursively search the KD-tree with pruning
		nearestNeighborValueRecurse(m_root, key, pQueue);

		// Count occurrences of all size_t in the kNN set
		std::unordered_map<size_t, int> counter;
		while (!pQueue.empty()) {
			++counter[pQueue.dequeueMin()];
		}

		// Return the most frequent element in the kNN set
		size_t result;
		int cnt = -1;
		for (const auto& p : counter) {
			if (p.second > cnt) {
				result = p.first;
				cnt = p.second;
			}
		}

		return result;
	}

	std::vector<std::pair<float, Point>> KDTree::kNN(const Point& key, std::size_t k) const
	{
		BoundedPQueue pQueue(k); 
		if (empty()) return std::vector<std::pair<float, Point>>{};

		nearestNeighborRecurse(m_root, key, pQueue);

		std::vector<std::pair<float, Point>> result;
		while (!pQueue.emptyPoints()) {
			result.push_back(pQueue.dequeuePoint());
		}

		return result;
	}
}