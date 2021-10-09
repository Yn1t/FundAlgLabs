#include "Relation.h"
#include <algorithm>

int main()
{

	try
	{
		Compare<int>* comp = new CompareInt;
		Relation<int, int> rel;

		rel.add_index(Relation<int, int>::Bin_tree, comp, "number, money");

		int arr[20];
		for (int i = 0; i < 20; ++i)
		{
			arr[i] = i;
		}

		random_shuffle(begin(arr), end(arr));

		for (int i = 0; i < 20; ++i)
			rel.insert(arr[i], i);

		rel.insert(21, 21).insert(22, 21).insert(39, 100);

		cout << rel.remove(arr[10]) << endl;
		cout << rel.find(39, "number, money");

		rel.delete_index("number, money");

	}
	catch (ExceptionTreeIsNotExist exc)
	{
		std::cout << exc.what() << endl;
	}
	catch (ExceptionIndexErr exc)
	{
		std::cout << exc.what() << endl;
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