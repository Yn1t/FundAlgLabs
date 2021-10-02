#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include "stdarg.h"
using namespace std;

typedef struct {
	double x;
	double y;
} point;

vector<string> find_pathes(bool (*function)(string str, string substr), string substr, int count, ...);
bool is_substr(string str, string substr);
bool is_convex(int count, ...);
double solution_pol(double x, int degree, ...);
int base_founder(string number);
string string_sum(string num_1, string num_2, int base);

void function_1();
void function_2();
void function_3();
void function_4(char* file_name);
void function_5(int base, int count, ...);
void function_6(string filename);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "russian");
	cout << "Petrov Nikita Olegovich, M8O-210B-20" << endl;

	cout << "Задача No 1, вывести все пути файлов, в которых найдётся нужная подстрока" << endl;
	cout << "Результаты :" << endl;

	function_1();

	cout << "Задача No 2, определить, является ли многоугольник выпуклым, возьмём многоугольник с точками : " << endl;
	function_2();

	cout << "Задача No 3, решение уравнения y = x^2 + 2*x + 1 с x равным 3 :" << endl;
	function_3();

	cout << "Задача No 4 : см. файл C:\\Users\\Yn1t\\source\\repos\\Лаба 1, Курс 2;" << endl;
	function_4(argv[1]);

	string numbers[] = { "0", "0", "0" };
	function_5(2, 3, numbers[0], numbers[1], numbers[2]);

	return 0;
}

void function_1()
{
	string str[] = { "C:\\Users\\Yn1t\\source\\repos\\FundAlgLabs\\Lab1\\Lab1Task11\\File_1.txt",
		"C:\\Users\\Yn1t\\source\\repos\\FundAlgLabs\\Lab1\\Lab1Task11\\File_2.txt",
		"C:\\Users\\Yn1t\\source\\repos\\FundAlgLabs\\Lab1\\Lab1Task11\\File_3.txt" };

	vector<string> pathes = find_pathes(is_substr, "", 3, str[0], str[1], str[2]);

	for (auto path : pathes)
		cout << path << endl;
}

bool is_substr(string str, string substr)
{
	int j = 0;

	if (!substr.length())
		return true;
	for (int i = 0; str[i] != '\0'; ++i)
		if (str[i] == substr[j])
		{
			while (str[i] == substr[j] && substr.length() != j)
			{
				++i;
				++j;
			}

			if (substr.length() == j)
				return true;
			else
				j = 0;
			i -= 1;
		}


	return false;
}

vector<string> find_pathes(bool (*function)(string str, string substr), string substr, int count, ...)
{
	vector<string> result;
	va_list arg;
	va_start(arg, count);

	for (int i = 0; i < count; ++i)
	{
		string filename;
		filename = va_arg(arg, string);

		ifstream file(filename);

		bool flag = true;

		int j = 0;
		string str, new_str = "\0";

		while (file && flag)
		{
			str = new_str;

			char word = 0;
			for (; j < substr.length() * 2 && word != -1; ++j)
			{
				word = file.get();
				if (word != -1)
					str += word;
			}

			new_str = "\0";

			if (function(str, substr))
			{
				result.push_back(filename);
				flag = false;
			}
			else
			{
				j = 0;
				if (word != -1)
					for (; j < substr.length(); ++j)
						new_str += str[j + substr.length()];
				else
					flag = false;
			}
		}
	}

	va_end(arg);

	return result;
}

void function_2()
{
	const int pointsCount = 4;
	point points[] = { 0, 0, 3, 3, 3, 4, 3, -2 };


	for (int i = 0; i < pointsCount; ++i)
		cout << "x = " << points[i].x << ", y = " << points[i].y << endl;

	if (is_convex(pointsCount, points[0], points[1], points[2], points[3]))
		cout << "Многоугольник выпуклый" << endl;
	else
		cout << "Многоугольник невыпуклый" << endl;
}

bool is_convex(int count, ...)
{
	vector<point> points;
	va_list arg;
	va_start(arg, count);

	for (int i = 0; i < count; ++i)
		points.push_back(va_arg(arg, point));

	va_end(arg);

	for (int i = 0; i < count - 2; ++i)
	{
		point vector_1{ points[i + 1].x - points[i].x, points[i + 1].y - points[i].y };
		point vector_2{ points[i + 2].x - points[i + 1].x, points[i + 2].y - points[i + 1].y };

		double vector_1_length = sqrt(pow(vector_1.x, 2) + pow(vector_1.y, 2));
		double vector_2_length = sqrt(pow(vector_2.x, 2) + pow(vector_2.y, 2));

		double cos_a = (vector_1.x * vector_2.x + vector_1.y * vector_2.y) / (vector_1_length * vector_2_length);

		if (cos_a < 0)
			return false;
	}

	return true;
}

void function_3()
{
	cout << solution_pol(3.0, 2, 1.0, 2.0, 1.0) << endl;
}

double solution_pol(double x, int degree, ...)
{
	double result = 0;
	va_list(arg);
	va_start(arg, degree);

	for (int i = 0; i <= degree; ++i)
	{
		double coff = va_arg(arg, double);
		result = result * x + coff;
	}

	va_end(arg);

	return result;
}

int base_founder(string number)
{
	char max;

	max = number[0];

	for (int i = 0; i < number.size(); ++i)
	{
		if (max < number[i])
			max = number[i];
	}

	max += 1;

	if (!isdigit(max))
		return max - 'A' + 10;
	else
		return max - '0';
}

void function_4(char* filename)
{
	ifstream file_in(filename);
	ofstream file_out("file_out.txt");

	while (file_in)
	{
		string nums;
		getline(file_in, nums);
		int i = 0;

		while (i != nums.size() + 1)
		{
			string number = "";

			if (nums[i] >= '0')
			{
				while (nums[i] >= '0')
				{
					number.push_back(nums[i]);
					++i;
				}

				int base = base_founder(number);
				int result = 0;

				for (int j = 0; j < number.size(); ++j)
					if (isdigit(number[j]))
						result = result * base + (number[j] - '0');
					else
						result = result * base + (number[j] - 'A' + 10);

				file_out << number << " " << base << " " << result << endl;
			}

			++i;
		}
	}
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

void function_6(string filename)
{

}