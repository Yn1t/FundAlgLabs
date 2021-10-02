#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stdarg.h"
using namespace std;

vector<string> find_pathes(bool (*function)(string str, string substr), string substr, int count, ...);
bool is_substr(string str, string substr);

int main()
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