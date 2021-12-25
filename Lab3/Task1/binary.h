#pragma once
#include "../../Lab2/Task1/compare.h"
#include <iostream>
#include <vector>

template<class Key, class Value>
class Binary_heap
{
	class Node
	{
	public:
		Node(Key key, Value value)
		{
			this->key = key;
			this->value = value;
		}
		Key key;
		Value value;
	};

	vector<Node> heap;
	Compare<Key>* comparator;
public:
	Binary_heap<Key, Value>(Compare<Key>* comparator)
	{
		this->comparator = comparator;
	}

	void insert(const Node node)
	{
		heap.push_back(node);
		int i = heap.size() - 1;
		int parent = (i - 1) / 2;

		while (i > 0 && comparator->compare(heap[parent].key, heap[i].key) > 0)
		{	
			Node temp = heap[i];
			heap[i] = heap[parent];
			heap[parent] = temp;

			i = parent;
			parent = (i - 1) / 2;
		}
	}

	const Value get_min()
	{
		Value res = heap[0].key;
		heap[0] = heap[heap.size() - 1];
		heap.pop_back();
		this->heapify(0);
		return res;
	}

	void heapify(int i)
	{
		int left, right, max_child;

		while (1)
		{
			left = 2 * i + 1;
			right = 2 * i + 2;
			max_child = i;

			if (left < heap.size() && comparator->compare(heap[left].key, heap[max_child].key) < 0)
			{
				max_child = left;
			}

			if (right < heap.size() && comparator->compare(heap[right].key, heap[max_child].key) < 0)
			{
				max_child = right;
			}

			if (max_child == i)
			{
				break;
			}

			Node temp = heap[i];
			heap[i] = heap[max_child];
			heap[max_child] = temp;
			i = max_child;
		}
	}

	void print_heap()
	{
		for (int i = 0; i < heap.size(); ++i)
		{
			std::cout << "Key = " << heap[i].key << ", Value = " << heap[i].value << std::endl;
		}
	}

	int get_heapsize()
	{
		return heap.size();
	}

	void merge(Binary_heap& second_heap)
	{
		while (second_heap.get_heapsize() != 0)
		{
			this->insert(second_heap.get_min());
		}
	}
};
