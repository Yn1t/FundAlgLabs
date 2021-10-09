#pragma once
#include "..\Task1\binary_tree.h"
#include "..\Task1\tree.h"

template <class Key, class Value>
class Avl_tree final : public Binary_tree <Key, Value>
{
	using Tree<Key, Value>::Node;
	class AVLNode final : public Binary_tree<Key, Value>::BNode
	{
	public:
		typename AVLNode(Key key, Value value) : Binary_tree<Key, Value>::BNode(key, value)
		{
			this->height = 0;
		};
		int height;
		AVLNode& recursive_height(int height)
		{
			int h_first = 0;
			int h_second = 0;
			if (this->right)
			{
				((AVLNode*)this->right)->recursive_height(height - 1);
				h_first = ((AVLNode*)this->right)->height;
			}

			if (this->left)
			{
				((AVLNode*)this->left)->recursive_height(height - 1);
				h_second = ((AVLNode*)this->left)->height;
			}

			this->height = (h_first >= h_second ? h_first : h_second) + 1;

			return *this;
		};
		AVLNode& balance()
		{
			if (this->balance_factor() == 2)
			{
				if (((AVLNode*)this->right)->balance_factor() < 0)
				{
					this->right->right_rotate();
					this->recursive_height(this->height);
				}
				this->left_rotate();
				this->recursive_height(this->height);
			}
			else if (this->balance_factor() == -2)
			{
				if (((AVLNode*)this->left)->balance_factor() > 0)
				{
					this->left->left_rotate();
					this->recursive_height(this->height);
				}
				this->right_rotate();
				this->recursive_height(this->height);
			}

			return *this;
		}
		int balance_factor()
		{
			return ((AVLNode*)this->right)->height_node() - ((AVLNode*)this->left)->height_node();
		};
		int height_node()
		{
			return this ? this->height : 0;
		};
		AVLNode& fix_height()
		{
			int height_left = 0;
			int height_right = 0;
			AVLNode* temp_node = (AVLNode*)this;
			height_left = ((AVLNode*)temp_node->left)->height_node();
			height_right = ((AVLNode*)temp_node->right)->height_node();
			temp_node->height = (height_left > height_right ? height_left : height_right) + 1;
			return *this;
		};
	};

	class Find_template_avl_tree final : public Binary_tree<Key, Value>::Find_template_binary_tree
	{
	protected:
		typename void after_find() override {};
	};

	class Delete_template_avl_tree final : public Binary_tree<Key, Value>::Delete_template_binary_tree
	{
	protected:
		typename void after_delete(Node*& root) override
		{
			while (!this->st.empty())
			{
				int temp_height = 0;
				AVLNode* temp_node = (AVLNode*)this->st.top();
				temp_node->fix_height();

				temp_node->balance();

				this->st.pop();
			}
		};
	};

	class Insert_template_avl_tree final : public Binary_tree<Key, Value>::Insert_template_binary_tree
	{
	protected:
		typename void after_insert() override
		{
			while (!this->st.empty())
			{
				int temp_height = 0;
				AVLNode* temp_node = (AVLNode*)this->st.top();
				temp_node->fix_height();

				temp_node->balance();

				this->st.pop();
			}
		};
		typename Binary_tree<Key, Value>::BNode* create_node(const Key& key, const Value& value) override
		{
			return new AVLNode(key, value);
		};
	};

public:
	typename Avl_tree<Key, Value>(Compare<Key>* comparator) : Binary_tree<Key, Value>(comparator)
	{
		delete this->finder_;
		this->finder_ = new Find_template_avl_tree;
		delete this->deleter_;
		this->deleter_ = new Delete_template_avl_tree;
		delete this->inserter_;
		this->inserter_ = new Insert_template_avl_tree;
	};
};