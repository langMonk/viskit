///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///
/// credits: https://github.com/junjiedong/KDTree
///

#pragma once

#include <stdexcept>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

#include <viskit/viskit/Structures.h>
#include <viskit/graph/generate/BoundedPQueue.h>

using namespace viskit::graph;

namespace viskit::graph::generate
{
	class KDTree
	{
		// public construction and destruction methods
	public:
		KDTree(std::vector<std::pair<DataPoint, size_t>>& points, size_t dim);

		~KDTree();

		KDTree(const KDTree& rhs);
		KDTree& operator=(const KDTree& rhs);

		// public methods
	public:
		[[nodiscard]] std::size_t size() const;
		[[nodiscard]] bool empty() const;

		[[nodiscard]] bool contains(const DataPoint& pt) const;

		void insert(const DataPoint& pt, const size_t& value = size_t());

		size_t& operator[](const DataPoint& pt);

		size_t& at(const DataPoint& pt);
		[[nodiscard]] const size_t& at(const DataPoint& pt) const;

		[[nodiscard]] std::vector<std::pair<float, DataPoint>> kNN(const DataPoint& key, std::size_t k) const;

		// internal sub-types
	private:
		struct Node
		{
			DataPoint point;
			Node* left;
			Node* right;
			int level;
			size_t value;
			Node(const DataPoint& _pt, int _level, const size_t& _value = size_t()) :
				point(_pt), left(nullptr), right(nullptr), level(_level), value(_value) {}
		};

		// private methods
	private:
		[[nodiscard]] Node* buildTree(typename std::vector<std::pair<DataPoint, size_t>>::iterator start,
			typename std::vector<std::pair<DataPoint, size_t>>::iterator end, int currLevel) const;

		Node* findNode(Node* currNode, const DataPoint& pt) const;

		void nearestNeighborRecurse(const Node* currNode, const DataPoint& key, BoundedPQueue& pQueue) const;

		Node* deepcopyTree(Node* root);

		void freeResource(Node* currNode);

		//private members
	private:
		Node* m_root;

		std::size_t m_sizePoints{};

		std::size_t m_size;

	};
}
