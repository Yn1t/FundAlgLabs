#pragma once
#include "..\Task1\binary_tree.h"
#include "..\Task1\tree.h"

template <class Key, class Value>
class RB_tree : public Binary_tree<Key, Value>
{
	using Binary_tree<Key, Value>::BNode;
	using Tree<Key, Value>::Node;

	class RBNode final : public Binary_tree<Key, Value>::BNode
	{
	public:
		typename RBNode(Key key, Value value) : BNode(key, value) {};

		typename RBNode& swap_colour()
		{

		};
		enum Colors { black, red };
		Colors clr = black;
		RBNode* get_uncle(const RBNode* node)
		{
			if (this->left != nullptr)
				if (this->left->key != node->key)
					return ((RBNode*)this->left);
				else
					return ((RBNode*)this->right);
			else
				return ((RBNode*)this->left);
		};
	};

	class Find_template_RB_tree final : public Binary_tree<Key, Value>::Find_template_binary_tree
	{
	protected:
		typename void after_find() override {};
	};

	class Insert_template_RB_tree final : public Binary_tree<Key, Value>::Insert_template_binary_tree
	{
	protected:
		typename void after_insert() override
		{
			RBNode* current;
			RBNode* parent;
			RBNode* uncle;
			RBNode* grand_parent;

			while (!this->st.empty())
			{
				// case 1
				if (this->st.size() == 1)
				{
					((RBNode*)this->st.top())->clr = RBNode::black;
					return;
				}
				else
					((RBNode*)this->st.top())->clr = RBNode::red;

				// case 2
				current = (RBNode*)this->st.top();
				this->st.pop();

				if (((RBNode*)this->st.top())->clr == RBNode::black)
					return;

				parent = (RBNode*)this->st.top();

				this->st.pop();

				grand_parent = ((RBNode*)this->st.top());

				uncle = grand_parent->get_uncle(parent);

				// case 3
				if (uncle && uncle->clr == RBNode::red)
				{
					parent->clr = RBNode::black;
					uncle->clr = RBNode::black;
					grand_parent->clr = RBNode::red;
					continue;
				}

				// case 4
				if (current == parent->right && parent == grand_parent->left)
					parent->left_rotate();
				else if (current == parent->left && parent == grand_parent->right)
					parent->right_rotate();

				// case 5
				if (current == parent->left && parent == grand_parent->left)
					grand_parent->right_rotate();
				else
					grand_parent->left_rotate();

				return;
				//this->st.pop();
			}
		};
		typename Binary_tree<Key, Value>::BNode* create_node(const Key& key, const Value& value)
		{
			return new RBNode(key, value);
		};
	};

	class Delete_template_RB_tree final : public Binary_tree<Key, Value>::Delete_template_binary_tree //,  Tree<Key, Value>::Node
	{
	protected:
		typename void after_delete(Node*& root) override
		{
			RBNode* current;
			RBNode* parent;
			RBNode* uncle;
			RBNode* grand_parent;

			if (this->st.size() == 1 && (((RBNode*)this->st.top())->left || ((RBNode*)this->st.top())->right))
			{
				if (((RBNode*)this->st.top())->left == nullptr)
					((RBNode*)((RBNode*)this->st.top())->right)->clr = RBNode::black;
				else
					((RBNode*)((RBNode*)this->st.top())->left)->clr = RBNode::black;
			}

			if (this->st.size() == 1)
			{
				current = ((RBNode*)this->st.top());
				this->st.pop();
				current = nullptr;;
				return;
			}

			if (((RBNode*)this->st.top())->clr == RBNode::red)
			{
				delete ((RBNode*)this->st.top());
				this->st.pop();

				return;
			}

			if (this->st.size() > 1)
			{
				int result;
				parent = (RBNode*)this->st.top();
				current = parent;
				this->st.pop();
				grand_parent = ((RBNode*)this->st.top());

				if (grand_parent->right == nullptr)
				{
					uncle = (RBNode*)grand_parent->left;
					parent = (RBNode*)grand_parent->right;
				}
				else if (grand_parent->left == nullptr)
				{
					uncle = (RBNode*)grand_parent->right;
					parent = (RBNode*)grand_parent->left;
				}
				else if (this->comparator->compare(grand_parent->right->key, parent->key) == -1)
				{
					uncle = (RBNode*)grand_parent->left;
					parent = (RBNode*)grand_parent->right;
				}
				else
				{
					uncle = (RBNode*)grand_parent->right;
					parent = (RBNode*)grand_parent->left;
				}

				current = nullptr;
				delete current;

				while (this->st.size())
				{
					// case 2
					if (uncle != nullptr && uncle->clr == RBNode::red)
					{
						if (uncle == grand_parent->left)
						{
							parent = (RBNode*)uncle->left;
							uncle = (RBNode*)uncle->right;
							grand_parent->right_rotate();
						}
						else
						{
							parent = (RBNode*)uncle->right;
							uncle = (RBNode*)uncle->left;
							grand_parent->left_rotate();
						}
						if (grand_parent->left == parent)
							grand_parent = (RBNode*)grand_parent->right;
						else
							grand_parent = (RBNode*)grand_parent->left;
					}
					// case 3
					if (grand_parent->clr == RBNode::black &&
						uncle->clr == RBNode::black &&
						(uncle->left == nullptr || ((RBNode*)uncle->left)->clr == RBNode::black) &&
						(uncle->right == nullptr || ((RBNode*)uncle->right)->clr == RBNode::black))
					{
						uncle->clr = RBNode::red;


						parent = (RBNode*)this->st.top();
						this->st.pop();
						if (this->st.size())
						{
							grand_parent = (RBNode*)this->st.top();
							uncle = grand_parent->get_uncle(parent);
						}
						continue;
					}
					// case 4
					if (uncle && grand_parent->clr == RBNode::red &&
						uncle->clr == RBNode::black &&
						(uncle->left == nullptr || ((RBNode*)uncle->left)->clr == RBNode::black) &&
						(uncle->right == nullptr || ((RBNode*)uncle->right)->clr == RBNode::black))
					{
						uncle->clr = RBNode::red;
						grand_parent->clr = RBNode::black;
						return;
					}
					// case 5 
					if (uncle || uncle->clr == RBNode::black)
					{
						if (uncle == grand_parent->right &&
							(uncle->right == nullptr || ((RBNode*)uncle->right)->clr == RBNode::black) &&
							uncle->left && ((RBNode*)uncle->left)->clr == RBNode::red)
						{
							uncle->right_rotate();
						}
						else if (uncle == grand_parent->left &&
							(uncle->left == nullptr || ((RBNode*)uncle->left)->clr == RBNode::black) &&
							uncle->right && ((RBNode*)uncle->right)->clr == RBNode::red)
						{
							uncle->left_rotate();
						}
					}

					// case 6
					if (uncle == grand_parent->right)
					{
						if (uncle->right)
							((RBNode*)uncle->right)->clr = RBNode::black;
						grand_parent->left_rotate();
					}
					else
					{
						if (uncle->left)
							((RBNode*)uncle->left)->clr = RBNode::black;
						grand_parent->right_rotate();
					}
					return;
				}
			}
			else
			{
				this->st.top() = nullptr;
				this->st.pop();
			}
		};
		void delete_node_(Node* node) override {};
	};

public:
	typename RB_tree<Key, Value>(Compare<Key>* comparator) : Binary_tree<Key, Value>(comparator)
	{
		delete this->finder_;
		this->finder_ = new Find_template_RB_tree;
		delete this->deleter_;
		this->deleter_ = new Delete_template_RB_tree;
		delete this->inserter_;
		this->inserter_ = new Insert_template_RB_tree;
	};

	typename void print_node(const RBNode* node, int depth)
	{
		for (int i = 0; i < depth; i++)
			cout << "\t";
		if (node->clr == RBNode::black)
			cout << "B=";
		else
			cout << "R=";
		cout << node->key << endl;
	};

	typename void print_tree(const Tree<Key, Value>::Node* _node, int depth)
	{
		if (_node == nullptr)
			return;
		print_tree(((BNode*)_node)->right, depth + 1);
		print_node((RBNode*)_node, depth);
		print_tree(((BNode*)_node)->left, depth + 1);
	};

	typename void print_RB_tree()
	{
		print_tree(this->root, 0);
	};
};