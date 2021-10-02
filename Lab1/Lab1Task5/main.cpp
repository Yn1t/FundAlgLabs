#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stdarg.h"
using namespace std;

string string_sum(string num_1, string num_2, int base);
void function_5(int base, int count, ...);

int main()
{
	string numbers[] = { "0", "0", "0" };
	function_5(2, 3, numbers[0], numbers[1], numbers[2]);

	return 0;
}

void function_5(int base, int count, ...)
{

	va_list arg;
	va_start(arg, count);

	string result = "";
	string num;

	for (int i = 0; i < count; ++i)
	{
		num = va_arg(arg, string);
		result = string_sum(result, num, base);
	}

	cout << result << endl;

	va_end(arg);
}

string string_sum(string num_1, string num_2, int base)
{
	string result = "";
	int rem = 0;
	int i, j;
	char res;

	for (i = num_1.size() - 1, j = num_2.size() - 1; i >= 0 && j >= 0; --i, --j)
	{
		int num1;
		int num2;

		if (num_1[i] >= 'A')
			num1 = num_1[i] - 'A' + 10;
		else
			num1 = num_1[i] - '0';

		if (num_2[j] >= 'A')
			num2 = num_2[j] - 'A' + 10;
		else
			num2 = num_2[j] - '0';

		if ((num1 + num2 + rem) % base >= 10)
		{
			rem = num1 + num2 + rem;
			res = rem % base + 'A' - 10;
			result = res + result;
			rem = rem / base;
		}
		else
		{
			rem = num1 + num2 + rem;
			res = rem % base + '0';
			result = res + result;
			rem = rem / base;
		}
	}

	if (i >= 0)
	{
		while (i >= 0)
		{
			if (num_1[i] - 'A' >= 0)
			{
				rem = num_1[i] - 'A' + 10 + rem;
				res = rem % base + 'A' - 10;
				result = res + result;
				rem = rem / base;
			}
			else
			{
				rem = (num_1[i] - '0') + rem;
				res = rem % base + '0';
				result = res + result;
				rem = rem / base;
			}
			--i;
		}
	}
	else if (j >= 0)
	{
		while (j >= 0)
		{
			if (num_2[j] - 'A' >= 0)
			{
				rem = num_2[j] - 'A' + 10 + rem;
				res = rem % base + 'A' - 10;
				result = res + result;
				rem = rem / base;
			}
			else
			{
				rem = (num_2[j] - '0') + rem;
				res = rem % base + '0';
				result = res + result;
				rem = rem / base;
			}
			--j;
		}
	}
	else
	{
		if (rem >= 10)
			res = rem + 'A' - 10;
		else
			res = rem + '0';
		result = res + result;
	}

	string new_str;
	i = 0;
	while (result[i] == '0' && i < result.length() - 1)
		++i;
	for (; i < result.length(); ++i)
		new_str += result[i];

	return new_str;
}