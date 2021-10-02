#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stdarg.h"
using namespace std;

int base_founder(string number);

int main(int argc, char* argv[])
{
	ifstream file_in(argv[1]);
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