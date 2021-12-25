#include <iostream>
#include <exception>
#include <algorithm>
#include "binary.h"
#include "binomial.h"
#include "..\..\Lab2\Task1\compare.h"

void binary_heap();
void binomial_heap();

int main()
{
	try
	{
		//binary_heap();
		binomial_heap();
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void binary_heap()
{
	Compare<int>* comp = new CompareInt;
	Binary_heap<int, int> heap(comp);

	int size = 200;

	int arr[200];

	for (int i = 0; i < size; ++i)
		arr[i] = i;

	random_shuffle(begin(arr), end(arr));

	for (int i = 0; i < size; ++i)
	{
		heap.insert({ arr[i], i });
		//cout << arr[i] << endl;
	}

	for (int i = 0; i < size; ++i)
	{
		//heap.print_heap();
		cout << "##################################" << endl;
		cout << heap.get_min() << endl;
	}
}

void binomial_heap()
{
	Compare<int>* comp = new CompareInt;
	Binomial_heap<int, int> heap_1(comp);
	Binomial_heap<int, int> heap_2(comp);

	int size = 200;

	int arr[200];

	for (int i = 0; i < size; ++i)
	{
		arr[i] = i + 1;
	}

	random_shuffle(begin(arr), end(arr));

	for (int i = 0; i < size / 2; ++i)
	{
		heap_1.insert({ arr[i], i });
		//cout << arr[i] << endl;
	}

	for (int i = size / 2; i < size - 10; ++i)
	{
		heap_2.insert({ arr[i], i });
		//cout << arr[i] << endl;
	}
	for (int i = 0; i < 10; ++i)
		heap_1.insert({ 1, 1 });

	heap_1.merge(heap_2);

	cout << heap_1.find_min() << endl;

	for (int i = 0; i < size; ++i)
		cout << heap_1.exctract_min() << endl;

	cout << heap_1.find_min() << endl;
	/*for (int i = 0; i < size; ++i)
	{
		heap.print_heap();
		cout << "##################################" << endl;
		heap.get_min();
	}*/
}