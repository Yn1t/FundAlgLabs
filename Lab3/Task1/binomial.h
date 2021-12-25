#pragma once
#include "../../Lab2/Task1/compare.h"

template <class Key, class Value>
class Binomial_heap
{
	class Node
	{
	public:
		Node(Key key = 0, Value value = 0)
		{
			this->key = key;
			this->value = value;
		}
		Key key;
		Value value;
		Node* child = nullptr;
		Node* sibling = nullptr;
		int degree = 0;
	};

	Compare<Key>* comparator;
public:
	Node* root;
	Node* min;

	Binomial_heap<Key, Value>(Compare<Key>* comp)
	{
		this->comparator = comp;
		root = nullptr;
	}

	void insert(const Node& node)
	{
		Compare<Key>* comp = new CompareInt;
		Binomial_heap<Key, Value> heap(comp);
		heap.root = new Node(node.key, node.value);

		this->merge(heap);
	}

	void merge(Binomial_heap& second_heap)
	{
		if (this->root == nullptr)
		{
			this->root = second_heap.root;
			this->min = this->root;
			return;
		}
		else if (second_heap.root == nullptr)
			return;

		Node* curr_2 = second_heap.root;
		Node* parent;
		Node* curr_1;

		while (curr_2)
		{
			bool flag = false;
			parent = this->root;
			curr_1 = this->root;
			Node* tmp = curr_2->sibling;

			while (curr_1 != nullptr)
			{
				if (curr_1->degree >= curr_2->degree)
				{
					if (curr_1->degree == curr_2->degree)
						flag = true;
					break;
				}
				parent = curr_1;
				curr_1 = curr_1->sibling;
			}

			if (flag)
			{
				Node* tmp_s = nullptr;
				if (parent == this->root)
					tmp_s = this->root;

				curr_1 = merge_tree(parent, curr_1, curr_2);

				if (tmp_s != nullptr)
					parent = this->root;

				while (curr_1->sibling && curr_1->degree == curr_1->sibling->degree)
				{
					tmp_s = nullptr;
					if (parent == this->root)
						tmp_s = this->root;

					curr_1 = merge_tree(parent, curr_1, curr_1->sibling);

					if (tmp_s != nullptr)
						parent = this->root;
				}
			}
			else
			{
				if (parent != curr_1)
				{
					parent->sibling = curr_2;
					if (curr_1)
						curr_2->sibling = curr_1;
					else
						curr_2->sibling = nullptr;
				}
				else
				{
					curr_2->sibling = parent;
					this->root = curr_2;

				}
			}

			if (this->comparator->compare(curr_2->key, this->min->key) != 1)
			{
				this->min = curr_2;
			}

			curr_2 = tmp;
		}

		second_heap.root = nullptr;
	}

	Key exctract_min()
	{
		Node* curr = this->root;
		Node* prev = curr;
		Compare<Key>* comp = new CompareInt;
		Binomial_heap<Key, Value> heap(comp);
		Key r_key;

		while (curr != this->min)
		{
			prev = curr;
			curr = curr->sibling;
		}

		if (prev == curr)
			this->root = prev->sibling;
		else
			prev->sibling = prev->sibling->sibling;

		heap.root = curr->child;
		r_key = curr->key;
		curr = nullptr;

		this->merge(heap);

		curr = this->root;
		Node* new_min = curr;

		while (curr)
		{
			if (this->comparator->compare(new_min->key, curr->key) == 1)
				new_min = curr;
			curr = curr->sibling;
		}

		this->min = new_min;

		return r_key;
	}

	Key find_min()
	{
		if (this->root)
			return this->min->key;
		else
			throw runtime_error("Heap is empty");
	}

	Node*& merge_tree(Node* p, Node* curr, Node* curr_2)
	{
		if (p == curr)
		{
			if (this->comparator->compare(p->key, curr_2->key) == -1)
			{
				if (p->sibling == curr_2)
					p->sibling = p->sibling->sibling;
				curr_2->sibling = p->child;
				p->child = curr_2;
			}
			else
			{
				if (p->sibling == curr_2)
					curr_2->sibling = p->sibling->sibling;
				else
					curr_2->sibling = p->sibling;
				this->root = curr_2;
				p->sibling = curr_2->child;
				this->root->child = p;
			}
			this->root->degree++;
			return this->root;
		}
		else
		{
			if (this->comparator->compare(p->sibling->key, curr_2->key) == -1)
			{
				if (p->sibling->sibling == curr_2)
					curr->sibling = curr->sibling->sibling;
				curr_2->sibling = curr->child;
				curr->child = curr_2;
				curr->degree++;
				return p->sibling;
			}
			else
			{
				Node* tmp = p->sibling;
				if (curr->sibling == curr_2)
					p->sibling = curr_2;
				else
					curr_2->sibling = p->sibling->sibling;
				curr->sibling = curr_2->child;
				p->sibling = curr_2;
				curr_2->child = curr;
				curr_2->degree++;
				return curr_2;
			}
		}

	}
};