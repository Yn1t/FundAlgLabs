#pragma once
#include "..\Task1\binary_tree.h"
#include "..\Task2\Avl_tree.h"
#include "..\Task2\RB_tree.h"
#include "..\Task2\Splay_tree.h"
#include "..\Task2\Two_three_tree.h"
#include "..\Task1\tree.h"
#include <map>
#include <string>
#include <vector>

template<class Key, class Value>
class Relation
{
	class Node
	{
	public:
		typename Node(Key key, Value value)
		{
			this->key = key;
			this->value = value;
		}
		Key key;
		Value value;
	};
	std::map<string, Tree<Key, Value>*> coll;
public:
	enum Tree_
	{
		Bin_tree,
		AVL_tree,
		RedBlack_tree,
		Splay_Tree,
		Two_Three_tree
	};
	vector<Node> nodes;

	typename ~Relation()
	{
		for (auto it : coll)
		{
			delete_index(it.first);
		}
	}

	typename Relation& add_index(Relation<Key, Value>::Tree_ tree, Compare<Key>*& comp, const string& index)
	{
		if (index.size() >= 32)
			throw ExceptionIndexErr();

		if (this->coll.find(index) != this->coll.end())
			throw ExceptionIndexErr();

		if (!isdigit(index[0]) && !isalpha(index[0]))
			throw ExceptionIndexErr();

		Tree<Key, Value>* tree_ = nullptr;

		if (tree == Bin_tree)
		{
			tree_ = new Binary_tree<Key, Value>(comp);
		}
		else if (tree == AVL_tree)
		{
			tree_ = new Avl_tree<Key, Value>(comp);
		}
		else if (tree == RedBlack_tree)
		{
			tree_ = new RB_tree<Key, Value>(comp);
		}
		else if (tree == Splay_Tree)
		{
			tree_ = new Splay_tree<Key, Value>(comp);
		}
		else if (tree == Two_Three_tree)
		{
			tree_ = new Two_three_tree<Key, Value>(comp);
		}
		else
		{
			throw ExceptionTreeIsNotExist();
		}

		if (coll.size())
		{
			auto it = coll.begin()->second;
			//it->second()->copy(tree_);
			it->copy(tree_);
		}
		else 
		{
			for (int i = 0; i < nodes.size(); ++i)
			{
				tree_->insert({ nodes[i].key, nodes[i].value });
			}
		}

		coll[index] = tree_;

		return *this;
	};

	typename Relation& delete_index(const string& index)
	{
		if (this->coll.find(index) == this->coll.end())
			throw ExceptionIndexErr();

		Tree<Key, Value>* tree_temp;
		tree_temp = this->coll[index];
		this->coll.erase(index);
		delete tree_temp;

		return *this;
	}

	typename Relation& insert(const Key& key, const Value& value)
	{
		for (auto it : coll)
			it.second->insert({ key, value });
		nodes.push_back({ key, value });

		return *this;
	};

	typename const Value remove(const Key& key)
	{
		Value temp_value;

		for (auto it : coll)
		{
			if (it.first == coll.begin()->first)
				temp_value = it.second->del(key);
			else
				it.second->del(key);
		}

		for (int i = 0; i < nodes.size(); ++i)
		{
			if (nodes[i].key == key)
				nodes.erase(nodes.begin() + i);
		}

		return temp_value;
	};

	typename const Value& find(const Key& key, const string& index)
	{
		if (this->coll.find(index) == this->coll.end())
			throw ExceptionIndexErr();

		return coll[index]->find(key);
	}
};