#pragma once
#include "compare.h"
#include "texpression.h"
#include <stack>
#include <memory>

template <class Key, class Value>
class Tree
{
protected:
	class Node
	{
		friend class Tree;
	public:
		typename Node(const Key& key, const Value& value)
		{
			this->key = key;
			this->value = value;
		};
		Key key;
		Value value;
	};

	class Find_template
	{
	public:
		typename const Value& invoke(Compare<Key>* comp, Node*& root, const Key& key)
		{
			this->comparator = comp;
			Value value = find(root, key);
			after_find();
			return value;
		};
	protected:
		Compare<Key>* comparator;
		stack<Node*> st;
		typename virtual const Value& find(Node*& root, const Key& key) = 0;
		typename virtual void after_find() = 0;
	};

	class Insert_template
	{
	public:
		typename void invoke(Compare<Key>* comp, Node*& root, const Node& node)
		{
			//comparator = make_shared<Compare<Key>>(comp);
			comparator = comp;
			add(root, node);
			after_insert();
		};
	protected:
		Compare<Key>* comparator;
		//shared_ptr<Compare<Key>> comparator;
		stack<Node*> st;
		typename virtual void add(Node*& root, const Node& node) = 0;
		typename virtual void after_insert() = 0;
	};

	class Delete_template
	{
	public:
		typename const Value& invoke(Compare<Key>* comp, Node*& root, const Key& key)
		{
			this->comparator = comp;
			Value temp_value;
			temp_value = delete_node(root, key);
			after_delete(root);
			return temp_value;
		};
	protected:
		Compare<Key>* comparator;
		stack<Node*> st;
		typename virtual const Value& delete_node(Node*& root, const Key& key) = 0;
		typename virtual void after_delete(Node*& root) = 0;
		typename void swap(Node* first_node, Node* second_node)
		{
			Key temp_key = first_node->key;
			Value temp_value = first_node->value;
			first_node->key = second_node->key;
			first_node->value = second_node->value;
			second_node->key = temp_key;
			second_node->value = temp_value;
		};
	public:
		typename virtual void delete_node_(Node* node) = 0;
	};

	//std::shared_ptr<typename Compare<Key>> comparator;
	Compare<Key>* comparator;
	Find_template* finder_;
	Delete_template* deleter_;
	Insert_template* inserter_;

	typename Tree<Key, Value>() {};

public:
	Node* root;

	typename Tree<Key, Value>(Compare<Key>* comparator)
	{
		this->root = nullptr;
		//this->comparator = std::shared_ptr<Compare<Key>> (comparator);
		this->comparator = comparator;
	};

	virtual void copy(Tree*& tree) = 0;

	typename virtual ~Tree<Key, Value>() {};

	typename const Value& find(const Key& key)
	{
		return this->finder_->invoke(&*this->comparator, this->root, key);
	};

	typename void insert(const Node& node)
	{
		this->inserter_->invoke(&*this->comparator, this->root, node);
	};

	typename const Value& del(const Key& key)
	{
		return this->deleter_->invoke(&*this->comparator, this->root, key);
	};

	typename virtual void delete_tree(Node* node) = 0;
};