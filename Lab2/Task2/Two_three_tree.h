#pragma once
#include "..\Task1\tree.h"

template<class Key, class Value>
class Two_three_tree : public Tree<Key, Value>
{
	using Tree<Key, Value>::Node;

	class TwoThreeNode
	{
		friend class Two_three_tree;
	public:
		typename TwoThreeNode(Node* node)
		{
			this->f_node = new Node(node->key, node->value);
		};
	private:
		TwoThreeNode* left = nullptr;
		TwoThreeNode* mid = nullptr;
		TwoThreeNode* right = nullptr;
		Node* s_node = nullptr;
		Node* f_node = nullptr;
		bool is_leaf()
		{
			return (this->left == nullptr && this->right == nullptr && this->mid == nullptr) ? true : false;
		};
		TwoThreeNode& swap(Node* node)
		{
			Key temp_key = this->f_node->key;
			Value temp_value = this->f_node->value;
			this->f_node->key = node->key;
			this->f_node->value = node->value;
			node->key = temp_key;
			node->value = temp_value;
			return *this;
		}
	};

	class Insert_template_23_tree final : public Tree<Key, Value>::Insert_template
	{
		stack<TwoThreeNode*> st_;
	public:
		typename void split(Node*& new_node, TwoThreeNode*& current_node)
		{
			if (this->st_.size() != 1)
				this->st_.pop();
			TwoThreeNode* previous_node = this->st_.top();

			int first_res = this->comparator->compare(new_node->key, current_node->f_node->key);
			int final_res = first_res;
			int second_res = this->comparator->compare(new_node->key, current_node->s_node->key);
			final_res += second_res;

			Node* middle_node;
			Node* new_node_right;
			Node* new_node_left;


			if (final_res == 0)
			{
				middle_node = new Node(new_node->key, new_node->value);
				new_node_left = new Node(current_node->f_node->key, current_node->f_node->value);
				new_node_right = new Node(current_node->s_node->key, current_node->s_node->value);
			}
			else if (final_res == -2)
			{
				middle_node = new Node(current_node->f_node->key, current_node->f_node->value);
				new_node_left = new Node(new_node->key, new_node->value);
				new_node_right = new Node(current_node->s_node->key, current_node->s_node->value);
			}
			else
			{
				middle_node = new Node(current_node->s_node->key, current_node->s_node->value);
				new_node_left = new Node(current_node->f_node->key, current_node->f_node->value);
				new_node_right = new Node(new_node->key, new_node->value);
			}

			if (previous_node->s_node == nullptr)
			{
				if (current_node == previous_node->left)
				{
					delete current_node;
					previous_node->left = new TwoThreeNode(new_node_left);
					previous_node->mid = new TwoThreeNode(new_node_right);
					previous_node->s_node = new Node(middle_node->key, middle_node->value);
				}
				else
				{
					previous_node->left = new TwoThreeNode(new_node_left);
					previous_node->mid = new TwoThreeNode(new_node_right);
					previous_node->s_node = new Node(middle_node->key, middle_node->value);
				}

				return;
			}

			if (current_node == previous_node)
			{
				if (current_node->is_leaf())
				{
					current_node->left = new TwoThreeNode(new_node_left);
					current_node->right = new TwoThreeNode(new_node_right);
					current_node->f_node = middle_node;
					delete current_node->s_node;
					current_node->s_node = nullptr;
				}
				else
				{
					TwoThreeNode* new_curr_left = new TwoThreeNode(new_node_left);
					TwoThreeNode* new_curr_left_r = nullptr;

					if (current_node->left->s_node)
					{
						new_curr_left_r = new TwoThreeNode(current_node->left->s_node);
						delete current_node->left->s_node;
						current_node->left->s_node = nullptr;
					}
					new_curr_left->left = current_node->left;
					current_node->left = new_curr_left;
					new_curr_left->right = new_curr_left_r;

					TwoThreeNode* new_curr_right = new TwoThreeNode(new_node_right);
					TwoThreeNode* new_curr_right_r = nullptr;

					new_curr_right->left = current_node->mid;
					new_curr_right->right = current_node->right;
					current_node->right = new_curr_left;
				}
			}
			else
			{
				current_node->f_node = new_node_left;
				current_node->s_node = new_node_right;
				split(middle_node, previous_node);
			}

			delete middle_node;
			delete new_node_left;
			delete new_node_right;
			return;
		}

	protected:
		typename void add(Node*& root, const Node& node) override
		{
			this->st_ = {};
			TwoThreeNode* current_node;
			TwoThreeNode* previous_node;
			bool flag = true;

			if (root)
			{
				current_node = (TwoThreeNode*)root;
				this->st_.push(current_node);
				previous_node = current_node;
			}
			else
			{
				Node* new_node = new Node(node.key, node.value);
				current_node = new TwoThreeNode(new_node);
				//current_node = new TwoThreeNode(root);
				root = (Node*)current_node;
				return;
			}

			//current_node->s_node = new Node(current_node->key, current_node->value);
			//current_node->s_node->key = current_node->key;;


			while (flag)
			{
				if (current_node->is_leaf())
				{
					if (current_node->s_node)
					{
						Node* new_node = new Node(node.key, node.value);
						this->split(new_node, current_node);
					}
					else
					{
						current_node->s_node = new Node(node.key, node.value);
						if (this->comparator->compare(current_node->f_node->key, current_node->s_node->key) == 1)
							current_node->swap(current_node->s_node);
					}
					flag = false;
				}
				else if (this->comparator->compare(node.key, current_node->f_node->key) == -1)
				{
					previous_node = current_node;
					current_node = current_node->left;
					this->st_.push(current_node);
				}
				else if (current_node->s_node == nullptr)
				{
					previous_node = current_node;
					current_node = current_node->right;
					this->st_.push(current_node);
				}
				else if (this->comparator->compare(node.key, current_node->s_node->key) == -1)
				{
					previous_node = current_node;
					current_node = current_node->mid;
					this->st_.push(current_node);
				}
				else
				{
					previous_node = current_node;
					current_node = current_node->right;
					this->st_.push(current_node);
				}
			}
		}
		typename void after_insert() override
		{

		}
	};

	class Find_template_23_tree final : public Tree<Key, Value>::Find_template
	{
	protected:
		typename const Value& find(Node*& root, const Key& key) override
		{
			Value temp_value;

			return temp_value;
		}
		void after_find() override
		{

		}
	};

	class Delete_template_23_tree final : public Tree<Key, Value>::Delete_template
	{
	protected:
		const Value& delete_node(Node*& root, const Key& key) override
		{
			Value temp_value;
			return temp_value;
		}
		void after_delete(Node*& root) override
		{

		}
	public:
		typename void delete_node_(Node* node) override
		{
			delete (TwoThreeNode*)node;
		};
	};

	typename void infix_(void (*function)(const Key&, const Value&, int d), const TwoThreeNode* node, int depth)
	{
		if (node == nullptr)
			return;

		TwoThreeNode* temp_node = (TwoThreeNode*)node;


		infix_(function, temp_node->left, depth + 1);
		function(node->f_node->key, node->f_node->value, depth);
		infix_(function, temp_node->mid, depth + 1);
		if (temp_node->s_node)
			function(temp_node->s_node->key, temp_node->s_node->value, depth);
		infix_(function, temp_node->right, depth + 1);
	}

public:

	typename Two_three_tree<Key, Value>(Compare<Key>* comparator) : Tree<Key, Value>(comparator)
	{
		this->finder_ = new Find_template_23_tree;
		this->deleter_ = new Delete_template_23_tree;
		this->inserter_ = new Insert_template_23_tree;
	}

	typename ~Two_three_tree<Key, Value>() {};

	typename void copy(Tree<Key, Value>*& tree)
	{

	}

	typename void delete_tree(Node* node) override
	{

	};

	typename void infix(void(*function)(const Key&, const Value&, int d))
	{
		infix_(function, (TwoThreeNode*)this->root, 0);
	}
};