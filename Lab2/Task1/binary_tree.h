#pragma once
#include "tree.h"
#include <functional>

template <class Key, class Value>
class Binary_tree : public Tree<Key, Value>
{
public:
	class BNode : public Tree<Key, Value>::Node
	{
		friend class Binary_tree;
	public:
		typename BNode(Key key, Value value) : Tree<Key, Value>::Node(key, value) {};
		typename void left_rotate()
		{
			swap(this->right);

			BNode* temp_node = this->right->right;

			this->right->right = this->right->left;
			this->right->left = this->left;
			this->left = this->right;
			this->right = temp_node;
		};
		typename void right_rotate()
		{
			swap(this->left);

			BNode* temp_node = this->right;

			this->right = this->left;
			this->left = this->right->left;
			this->right->left = this->right->right;
			this->right->right = temp_node;
		};
		typename BNode& swap(BNode* node)
		{
			Key temp_key;
			Value temp_value;
			temp_key = this->key;
			temp_value = this->value;
			this->key = node->key;
			this->value = node->value;
			node->key = temp_key;
			node->value = temp_value;
			return *this;
		}
		BNode* left = nullptr;
		BNode* right = nullptr;
	};
protected:
	class Find_template_binary_tree : public Tree<Key, Value>::Find_template
	{
	protected:
		typename const Value& find(Tree<Key, Value>::Node*& root, const Key& key) override
		{
			this->st = {};
			BNode* current_node;
			int last_result = -1;
			current_node = (BNode*)root;

			while (current_node && last_result)
			{
				switch (last_result = this->comparator->compare(key, current_node->key))
				{
				case (1):
					this->st.push(current_node);
					current_node = current_node->right;
					break;
				case (-1):
					this->st.push(current_node);
					current_node = current_node->left;
					break;
				case (0):
					break;
				default:
					throw TreeExceptionCompErr();
					break;
				}
			}

			this->st.push(current_node);

			if (last_result != 0)
				throw TreeExceptionNonExisted();

			return current_node->value;
		};
		typename virtual void after_find() {};
	};

	class Delete_template_binary_tree : public Tree<Key, Value>::Delete_template
	{
	protected:
		typename const Value& delete_node(Tree<Key, Value>::Node*& root, const Key& key) override
		{
			this->st = {};
			Value temp_value;
			BNode* current_node;
			BNode* previous_node;
			BNode* swap_node;
			BNode* temp;

			current_node = (BNode*)root;
			previous_node = (BNode*)root;

			int last_result = -2;

			while (current_node && current_node->key != key)
			{
				switch (last_result = this->comparator->compare(key, current_node->key))
				{
				case (1):
					this->st.push(current_node);
					previous_node = current_node;
					current_node = current_node->right;
					break;
				case (-1):
					this->st.push(current_node);
					previous_node = current_node;
					current_node = current_node->left;
					break;
				default:
					throw TreeExceptionCompErr();
					break;
				}
			}

			if (current_node == nullptr)
				throw TreeExceptionNonExisted();

			this->st.push(current_node);
			temp = current_node;
			temp_value = temp->value;

			if (current_node->left == nullptr && current_node->right == nullptr)
			{
				if (current_node->key == root->key)
				{
					previous_node = nullptr;
					root = nullptr;
				}
				else
				{
					if (last_result == 1)
						previous_node->right = nullptr;
					else
						previous_node->left = nullptr;
				}
			}
			else
			{
				if (current_node->left == nullptr)
				{
					if (root->key == current_node->key)
					{
						root = current_node->right;
					}
					else
					{
						if (last_result == 1)
						{
							previous_node->right = current_node->right;
						}
						else
							previous_node->left = current_node->right;
					}
				}
				else if (current_node->right == nullptr)
				{
					if (root->key == current_node->key)
					{
						root = current_node->left;
					}
					else
					{
						if (last_result == 1)
							previous_node->right = current_node->left;
						else
							previous_node->left = current_node->left;
					}
				}
				else
				{
					BNode* swap_node;
					swap_node = current_node;
					previous_node = current_node;
					current_node = current_node->left;

					if (current_node->right)
					{
						while (current_node->right)
						{
							this->st.push(current_node);
							previous_node = current_node;
							current_node = current_node->right;
						}

						this->st.push(current_node);
						temp = current_node;

						if (current_node->left)
							previous_node->right = current_node->left;
						else
							previous_node->right = nullptr;
					}
					else
					{
						this->st.push(current_node);
						temp = current_node;
						previous_node->left = nullptr;
					}
					this->swap(temp, swap_node);
				}
			}

			// TODO решить проблему удаления корня
			this->delete_node_(temp);
			return temp_value;
		};
		typename virtual void after_delete(Tree<Key, Value>::Node*& root) {};
	public:
		typename virtual void delete_node_(Tree<Key, Value>::Node* deleted_node)
		{
			if (this->st.size() != 1)
				delete ((BNode*)deleted_node);
			if (!this->st.empty())
				this->st.pop();
			deleted_node = nullptr;
		};
	};

	class Insert_template_binary_tree : public Tree<Key, Value>::Insert_template
	{
	protected:
		typename void add(Tree<Key, Value>::Node*& root, const Tree<Key, Value>::Node& node) override
		{
			this->st = {};
			BNode* current_node;
			BNode* previous_node = nullptr;
			int last_result;

			if (root)
			{
				current_node = (BNode*)(root);
			}
			else
			{
				current_node = new BNode(node.key, node.value);
				this->st.push(current_node);
				root = current_node;
				return;
			}

			while (current_node)
			{
				switch (last_result = this->comparator->compare(node.key, current_node->key))
				{
				case (1):
					previous_node = current_node;
					this->st.push(current_node);
					current_node = current_node->right;
					break;
				case (-1):
					previous_node = current_node;
					this->st.push(current_node);
					current_node = current_node->left;
					break;
				case (0):
					throw TreeExceptionIsExisted();
					break;
				default:
					throw TreeExceptionCompErr();
					break;
				}
			}

			current_node = create_node(node.key, node.value);

			this->st.push(current_node);

			if (last_result == 1)
				previous_node->right = current_node;
			else
				previous_node->left = current_node;
		};
		typename virtual void after_insert() {};
		typename virtual BNode* create_node(const Key& key, const Value& value)
		{
			return new BNode(key, value);
		};
	};

	typename void infix_(function<void(Key k, Value v, int d)> func, const Tree<Key, Value>::Node* node, int depth)
	{
		if (node == nullptr)
			return;

		BNode* temp_node = (BNode*)node;


		infix_(func, temp_node->left, depth + 1);
		func(node->key, node->value, depth);
		infix_(func, temp_node->right, depth + 1);
	};

	typename void prefix_(function<void(Key k, Value v, int d)> func, const Tree<Key, Value>::Node* node, int depth)
	{
		if (node == nullptr)
			return;

		BNode* temp_node = (BNode*)node;

		func(node->key, node->value, depth);
		prefix_(func, temp_node->left, depth + 1);
		prefix_(func, temp_node->right, depth + 1);
	};

	typename void postfix_(function<void(Key k, Value v, int d)> func, const Tree<Key, Value>::Node* node, int depth)
	{
		if (node == nullptr)
			return;

		BNode* temp_node = (BNode*)node;

		postfix_(func, temp_node->left, depth + 1);
		postfix_(func, temp_node->right, depth + 1);
		func(node->key, node->value, depth);
	};

public:
	typename Binary_tree<Key, Value>(Compare<Key>* comparator) : Tree<Key, Value>(comparator)
	{
		this->finder_ = new Find_template_binary_tree;
		this->deleter_ = new Delete_template_binary_tree;
		this->inserter_ = new Insert_template_binary_tree;
	};

	typename Binary_tree<Key, Value>(const Binary_tree<Key, Value>& tree)
	{
		this->comparator = tree.comparator;
		this->finder_ = new Find_template_binary_tree;
		this->deleter_ = new Delete_template_binary_tree;
		this->inserter_ = new Insert_template_binary_tree;
		delete_tree(this->root);
		this->root = nullptr;
		prefix_copy(tree.root);
	};

	typename Binary_tree<Key, Value>& operator=(const Binary_tree<Key, Value>& tree)
	{
		this->comparator = tree.comparator;
		delete_tree(this->root);
		this->root = nullptr;
		prefix_copy(tree.root);
		return *this;
	};

	typename void prefix_copy(Tree<Key, Value>::Node* node)
	{
		if (node == nullptr)
			return;

		BNode* temp_node = (BNode*)node;

		this->insert({ temp_node->key, temp_node->value });
		prefix_copy(temp_node->left);
		prefix_copy(temp_node->right);
	};

	typename void copy(Tree<Key, Value>*& tree)
	{
		vector<Tree<Key, Value>::Node> nodes;

		prefix([&nodes](const Key& k, const Value& v, int d) {nodes.push_back({ k, v }); });

		for (auto it : nodes)
		{
			tree->insert({ it.key, it.value });
		}
	}

	typename virtual ~Binary_tree<Key, Value>()
	{
		delete_tree(this->root);
	};

	typename void delete_tree(Tree<Key, Value>::Node* node) override
	{
		BNode* temp_node;
		temp_node = (BNode*)node;

		if (temp_node == nullptr)
			return;

		if (temp_node->left)
			delete_tree(temp_node->left);

		if (temp_node->right)
			delete_tree(temp_node->right);

		// TODO решить проблему
		if (this->root->key != temp_node->key)
			this->deleter_->delete_node_(temp_node);
	};

	typename void prefix(function<void(Key k, Value v, int d)> func)
	{
		prefix_(func, this->root, 0);
	};

	typename void infix(function<void(Key k, Value v, int d)> func)
	{
		infix_(func, this->root, 0);
	};

	typename void postfix(function<void(Key k, Value v, int d)> func)
	{
		postfix_(func, this->root, 0);
	};
};



