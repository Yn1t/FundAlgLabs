#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;



string op(string op);

int main(int argc, char* argv[])
{

	string argv_2;
	bool flag = false;
	ifstream file_in(argv[1]);

	if (argv[2])
		argv_2 = argv[2];

	if (argv_2 == "/trace")
	{
		ofstream file_trace(argv[3]);
		flag = true;
	}


	map<char, string> vect;

	while (file_in)
	{
		string str = "";
		int i = 0;
		char chr;
		file_in >> chr;
		while (chr != ';' || file_in)
		{
			if (chr == '%')
			{
				file_in >> chr;
				while (chr != '\n' && file_in)
					chr = file_in.get();
				file_in >> chr;
			}

			int bracket_count = 0;

			if (chr == '{')
			{
				bracket_count++;
				while (bracket_count != 0 && file_in)
				{
					if (file_in.get() == '}')
						bracket_count--;
					else if (file_in.get() == '{')
						bracket_count++;
				}
				file_in >> chr;
			}

			if (chr != '{' && chr != '%')
			{
				str += chr;
				file_in >> chr;
			}
		}

		i = 0;
		string op;

		char res = 0;

		while (str[i] != ':')
		{

			if (i == 0)
				if (str[i] >= 'A' && str[i] <= 'Z')
					res = str[i];
			
			if (str[i] == 'r')
				op += 'r';
			else if (str[i] == 'e')
				op += 'e';
			else if (str[i] == 'a')
				op += 'a';
			else if (str[i] == 'd')
				op += 'd';
			else if (str[i] == 'w')
				op += 'w';
			else if (str[i] == 'r')
				op += 'r';
			else if (str[i] == 'i')
				op += 'i';
			else if (str[i] == 't')
				op += 't';
			else if (str[i] == 'e')
				op += 'e'
			else
				printf("Error");

			if (op.length() == 4 || op.length() == 5)
				break;
			++i;
		}


	}
}


string op(string op)
{
	return "";
}