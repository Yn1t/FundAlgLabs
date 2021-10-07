#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;

string pre_parsing_instruct(string str);
string pre_parsing(string str);

class Inter {
	map<string, string> operations = { 
		{"add", "add"},
		{ "mult", "mult" },
		{ "sub", "sub" },
		{ "pow", "pow" },
		{ "div", "div" },
		{ "rem", "rem" }, 
		{ "xor", "xor" },
		{ "input", "input" },
		{ "output", "output" }, 
		{"=", "="}
	};
	map<string, string> order = { {"result_order", "left"}, {"op_order", "left"} };
	bool left_result = true;
	enum class Staples
	{
		left,
		right,
		left_between,
		right_between
	};
	Staples staple_order = Staples::left;
	map<string, int> vect;

public:
	Inter(string file_syntax, string file_instruct);
	~Inter();
	void Inter_Parcer(string syntax);
};

class Parser {
	string result_string;
public:
	Parser(string str, Inter inter);
	~Parser();
};

int main(int argc, char* argv[])
{
	char chr;
	int i = 0;

	Inter inter(argv[1], "file_in.txt");

	cout << "";

	return 0;
}

string pre_parsing_instruct(string str)
{
	string str_final = "";

	int i = 0;

	while (str.size() > i)
	{
		if (str[i] == '#')
		{
			while (str.size() > i)
				++i;
		}

		str_final += str[i];
		++i;
	}

	return str_final;
}

string pre_parsing(string str)
{
	string str_final;
	int i = 0;

	while (str.size() > i)
	{
		if (str[i] == '#')
			while (str[i] != '\n' && str[i] != i)
				++i;

		if (str[i] == '[')
		{
			int n = 1;

			while (n)
			{
				++i;
				if (str[i] == '[')
					n++;
				if (str[i] == ']')
					n--;
			}

			++i;
		}

		if (str[i] > ' ' && str[i] != '[')
		{
			str_final += str[i];
		}

		++i;
	}

	return str_final;
}

Parser::Parser(string str, Inter inter)
{
	result_string = "";
}

Parser::~Parser()
{

}

Inter::Inter(string file_syntax, string file_instruct)
{
	ifstream file_synt(file_syntax);

	while (file_synt)
	{
		string str_inst = "";
		char chr;
		chr = file_synt.get();

		while (chr != '\n' && file_synt)
		{
			str_inst += chr;
			chr = file_synt.get();
		}

		str_inst = pre_parsing_instruct(str_inst);

		if (str_inst[0] != '\0')
		{
			this->Inter_Parcer(str_inst);
		}
	}


}

Inter::~Inter()
{
	ifstream def("default.txt");

	//if (left_result)
		
}

void Inter::Inter_Parcer(string syntax)
{
	int i = 0;
	string command = "";

	while (syntax[i] != ' ' && syntax[i] != '\n')
	{
		command += syntax[i];
		++i;
	}

	if (command == "left=")
		left_result = true;
	else if (command == "right=")
		left_result = false;
	else if (command == "op()")
		staple_order = Staples::left;
	else if (command == "()op")
		staple_order = Staples::right;
	else if (command == "(op)()")
		staple_order = Staples::left_between;
	else if (command == "()(op)")
		staple_order = Staples::right_between;
	else if (operations[command].empty())
	{
		cout << "Error syntax" << endl;
		exit(-1);
	}
	else
	{
		
		++i;
		string new_command = "";

		while (syntax.size() > i)
		{
			new_command += syntax[i];
			++i;
		}

		operations[command] = new_command;
	}
}
