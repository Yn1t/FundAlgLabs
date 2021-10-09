#pragma once
#include "..\Task1\binary_tree.h"
#include "..\Task1\tree.h"

template<class Key, class Value>
class Splay_tree : public Binary_tree<Key, Value>
{
	using Tree<Key, Value>::Node;
	class SplayNode final : public Binary_tree<Key, Value>::BNode
	{

	public:
		typename SplayNode& splay(stack<Node*>& st)
		{
			SplayNode* current = (SplayNode*)st.top();
			SplayNode* parent;
			SplayNode* grand_parent = nullptr;

			if (st.size() == 1)
				return *this;

			st.pop();
			parent = (SplayNode*)st.top();
			st.pop();

			if (st.size())
				grand_parent = (SplayNode*)st.top();

			if (grand_parent)
			{
				if (grand_parent->left == parent && parent->left == this)
				{
					grand_parent->right_rotate();
					grand_parent->right_rotate();
				}
				else if (grand_parent->right == parent && parent->right == this)
				{
					grand_parent->left_rotate();
					grand_parent->left_rotate();
				}
				else if (grand_parent->left == parent && parent->right == this)
				{
					parent->left_rotate();
					grand_parent->right_rotate();
				}
				else
				{
					parent->right_rotate();
					grand_parent->left_rotate();
				}
				grand_parent->splay(st);
			}
			else
			{
				if (parent->left == current)
				{
					parent->right_rotate();
				}
				else
				{
					parent->left_rotate();
				}
			}

			return *this;
		}
		typename SplayNode** split()
		{
			SplayNode* temp_node = (SplayNode*)this->left;
			this->left = nullptr;
			SplayNode** arr = new SplayNode * [2];
			arr[0] = temp_node;
			arr[1] = this;
			return arr;
		};
		typename SplayNode& merge(SplayNode*& left_tree_root)
		{
			stack<Node*> st = {};

			SplayNode* max_node = left_tree_root;
			st.push((Node*)max_node);

			if (!max_node)
			{
				this->left = nullptr;
				return *this;
			}

			while (max_node->right)
			{
				max_node = (SplayNode*)max_node->right;
				st.push((Node*)max_node);
			}

			if (st.size())
				max_node->splay(st);

			this->left = left_tree_root;

			return *this;
		}
	};

	class Find_template_Splay_tree final : public Binary_tree<Key, Value>::Find_template_binary_tree
	{
	protected:
		typename void after_find() override
		{
			((SplayNode*)this->st.top())->splay(this->st);

			return;
		};
	};

	class Insert_template_Splay_tree final : public Binary_tree<Key, Value>::Insert_template_binary_tree
	{
	protected:
		typename void after_insert() override
		{
			((SplayNode*)this->st.top())->splay(this->st);

			return;
		};
	};

	class Delete_template_Splay_tree final : public Binary_tree<Key, Value>::Delete_template_binary_tree
	{
	protected:
		typename void after_delete(Node*& root) override
		{
			if (this->st.empty() || this->st.size() == 1)
				return;
			SplayNode* new_node = (SplayNode*)this->st.top();
			new_node->splay(this->st);

			new_node = (SplayNode*)root;
			SplayNode** arr;
			arr = new_node->split();
			arr[1]->merge(arr[0]);
		};
	};

public:
	typename Splay_tree<Key, Value>(Compare<Key>* comparator) : Binary_tree<Key, Value>(comparator)
	{
		delete this->finder_;
		this->finder_ = new Find_template_Splay_tree;
		delete this->deleter_;
		this->deleter_ = new Delete_template_Splay_tree;
		delete this->inserter_;
		this->inserter_ = new Insert_template_Splay_tree;
	}
};