#include <iostream>
#include "binary_tree.h"

template<typename Key, typename Value>
void print_node(Key key, Value value, int depth)
{
	cout << "Ключ : " << key << ", значение : " << value << ", глубина : " << depth << endl;
}

int main()
{
	setlocale(LC_ALL, "russian");
	Compare<int>* comp = new CompareInt;
	Binary_tree<int, int> tree(comp);

	try
	{
		tree.insert({ 3, 1 });
		tree.insert({ 1, 0 });
		tree.insert({ 0, 1 });
		tree.insert({ 2, 0 });
		tree.insert({ 4, 1 });
		tree.del(4);

		tree.prefix(print_node<int, int>);

		Binary_tree<int, int> tree_copy(tree);

		tree_copy = tree;

		cout << "Tree_copy key 6, value = " << tree_copy.find(6) << endl;
	}
	catch (TreeExceptionCompErr exc)
	{
		std::cout << exc.what() << endl;
	}
	catch (TreeExceptionIsExisted exc)
	{
		std::cout << exc.what() << endl;
	}
	catch (TreeExceptionNonExisted exc)
	{
		std::cout << exc.what() << endl;
	}
}