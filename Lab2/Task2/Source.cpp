#include <iostream>
#include "Avl_tree.h"
#include "RB_tree.h"
#include "Splay_tree.h"
#include "Two_three_tree.h"
#include <algorithm>

void avl_tree();
void rb_tree();
void splay_tree();
void two_three_tree();

template<typename Key, typename Value>
void print_node(Key key, Value value, int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "\t";
	cout << key <<  endl;
}
/*template<typename Key, typename Value>
void print_node(Key key, Value value, int depth)
{
	cout << "Ключ : " << key << ", значение : " << value << ", глубина : " << depth << endl;
}*/

int main()
{
	setlocale(LC_ALL, "russian");

	try
	{
		avl_tree();
		//rb_tree();
		//splay_tree();
		//two_three_tree();
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

void avl_tree()
{
	Compare<int>* comp = new CompareInt;
	Avl_tree<int, int> tree(comp);
	int arr[50];
	for (int i = 0; i < 50; ++i)
	{
		arr[i] = i;
	}

	random_shuffle(begin(arr), end(arr));

	for (int i = 0; i < 50; ++i)
	{
		tree.insert({ arr[i], i });
	}

	//for (int i = 0; i < 50; i += 1)
	{
		//tree.del(i);
	}
	tree.infix(print_node<int, int>);

	return;
}

void rb_tree()
{
	Compare<int>* comp = new CompareInt;
	RB_tree<int, int> tree(comp);

	int arr[200000];
	/*tree.insert({0, 1});
	tree.insert({ -2, 0 });
	tree.insert({ 2, 1 });
	tree.insert({ 1, 0 });
	tree.insert({ 3, 1 });
	tree.insert({ -1, 1 });
	tree.insert({ -5, 0 });
	tree.insert({ -6, 1 });
	tree.insert({ -4, 0 });
	tree.insert({ -3, 1 });*/
	for (int i = 0; i < 200000; ++i)
	{
		arr[i] = i;
	}

	random_shuffle(begin(arr), end(arr));

	for (int i = 0; i < 200000; ++i)
	{
		//cout << "################################################################" << endl;
		//tree.print_RB_tree();
		tree.insert({ arr[i], i });
	}
	//tree.print_RB_tree();

	for (int i = 0; i < 199999; i += 1)
	{
		//tree.print_RB_tree();
		//cout << "################################################################" << endl;
		tree.del(i);
	}
	tree.print_RB_tree();
	//Avl_tree<int, int> tree_copy(tree);
	//tree.print_RB_tree();

	return;
}

void splay_tree()
{
	Compare<int>* comp = new CompareInt;
	Splay_tree<int, int> tree(comp);

	int arr[200000];
	for (int i = 0; i < 200000; ++i)
	{
		arr[i] = i;
	}

	random_shuffle(begin(arr), end(arr));

	for (int i = 0; i < 200000; ++i)
	{
		//tree.infix(print_node);
		//cout << "################################################################" << endl;
		tree.insert({ arr[i], i });
	}

	//tree.find(1);
	//tree.infix(print_node);

	for (int i = 0; i < 199999; i++)
	{
		//tree.infix(print_node);
		//cout << "################################################################" << endl;
		tree.del(i);
	}

	tree.infix(print_node<int, int>);

	return;
}

void two_three_tree()
{
	/*Compare<int>* comp = new CompareInt;
	Two_three_tree<int, int> tree(comp);

	int arr[10];
	for (int i = 0; i < 10; ++i)
	{
		arr[i] = i;
	}

	random_shuffle(begin(arr), end(arr));

	for (int i = 0; i < 10; ++i)
	{
		tree.infix(print_node);
		cout << "################################################################" << endl;
		tree.insert({ arr[i], i });
	}

	//tree.find(1);
	//tree.infix(print_node);

	/*for (int i = 0; i < 199999; i++)
	{
		//tree.infix(print_node);
		//cout << "################################################################" << endl;
		tree.del(i);
	}

	//tree.infix(print_node);
	*/
	return;
}