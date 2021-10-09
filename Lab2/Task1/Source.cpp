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
		/*tree.insert({1, 8});
		tree.insert({ 0, 4 });
		tree.insert({ 9, 9 });
		tree.insert({ 10, 10 });
		tree.insert({ 2, 8 });
		tree.insert({ 4, 4 });
		tree.insert({ 3, 9 });
		tree.insert({ 6, 8 });
		tree.insert({ 5, 4 });
		cout << tree.find(3) << endl;
		cout << tree.find(5) << endl;
		cout << tree.find(1) << endl;
		tree.del(6);
		cout << tree.find(6) << endl;
		*/
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