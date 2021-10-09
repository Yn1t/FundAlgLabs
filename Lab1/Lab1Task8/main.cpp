#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <map>
#include <exception>
#include <string>
using namespace std;


class Parser;

struct Operator_struct {
	string op = "";
	string first = "";
	string second = "";
};

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
		{ "=", "=" }
	};
	bool left_result = true;
	enum Staples
	{
		Left,
		Right,
		Left_between,
		Right_between
	};
	Staples staple_order = Left;
	map<string, int> vect;
	Parser* parser = nullptr;

public:
	Inter(string file_syntax, string file_instruct);
	~Inter();
	void returnToDefault();
	void Inter_Parcer(string syntax);
	vector<string> split(const string& str, string del);
	string delete_space(const string& str);
	bool isdigitStr(string str);
	bool iscorrect_name(string str);
	bool iscorrect(string str);
	int operate(Operator_struct op, string result = "");
	int gorner_in(string number, int base);
	string gorner_out(int number, int base);
	int toNumber(string number);
};

class Parser {
	string result_string;
public:
	virtual Operator_struct parse(const string op) = 0;
};

class Parser_left : public Parser {
public:
	Operator_struct parse(const string op);
};

class Parser_right : public Parser {
public:
	Operator_struct parse(const string op);
};

class Parser_between : public Parser {
public:
	Parser_between() {};
	Operator_struct parse(const string op);
};

class Parser_right_between : public Parser {
public:
	Parser_right_between() {};
	Operator_struct parse(const string op);
};

int main(int argc, char* argv[])
{
	char chr;
	int i = 0;

	Inter inter(argv[1], "file_in.txt");

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

		if (str[i] != '[' && str[i] != '\n' && str[i] != '\t')
		{
			str_final += str[i];
		}

		++i;
	}

	return str_final;
}

vector<string> Inter::split(const string& str, string del)
{
	string first_arg;
	int i = 0;
	// abcbac 123  123
	while (str[i] != del[0] && str.size() > i)
	{
		first_arg += str[i];
		++i;
	}

	if (str.size() > i)
	{
		int j = 0;
		while (str[i] == del[j] && str[i] != ' ')
		{
			++i;
			++j;
		}

		if (j != del.size())
			throw new exception("Incorrect instructions, please use correct syntax;");
	}

	vector<string> strings;
	strings.push_back(first_arg);

	string second_arg;

	if (str.size() > i)
	{
		++i;
		while (str[i] != ';' && str.size() > i)
		{
			second_arg += str[i];
			++i;
		}
	}

	if (second_arg != "")
		strings.push_back(second_arg);

	return strings;
}

string Inter::delete_space(const string& str)
{
	string str_new = "";
	int i = 0;

	if (str[0] == ' ')
		while (str[i] == ' ')
			++i;

	int j = str.size() - 1;
	if (str.size() > i && str[j] == ' ')
		while (str[j] == ' ')
			--j;

	while (i <= j)
	{
		str_new += str[i];
		++i;
	}

	return str_new;
}

bool Inter::isdigitStr(string str)
{
	int i = 0, flag = 1;

	if (str[0] != '-')
	{
		flag = -1;
		++i;
	}

	for (i = 0; i < str.size(); ++i)
		if (!isdigit(str[i]))
			return false;
	return true;
}

bool Inter::iscorrect_name(string str)
{
	int i = 0;

	if (str.size() > 30 || str.empty())
		return false;

	if (isdigit(str[0]))
		return false;

	while (str.size() > i)
	{
		if (str[i] != '_' && !isdigit(str[i]) && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
			return false;
		++i;
	}

	return true;
}

bool Inter::iscorrect(string str)
{
	if (isdigitStr(str))
		return true;

	int i = 0;

	if (str.size() > 30 || str.empty())
		return false;

	if (isdigit(str[0]))
		return false;

	while (str.size() > i)
	{
		if (str[i] != '_' && !isdigit(str[i]) && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
			return false;
		++i;
	}

	return true;
}

int Inter::operate(Operator_struct op, string result)
{
	string arg_1, arg_2, oper;
	oper = op.op;

	if (isdigitStr(op.first))
		arg_1 = op.first;
	else if (!vect.count(op.first))
		throw new exception("Incorrect instructions, please use correct syntax;");
	else
		arg_1 = op.first;

	if (isdigitStr(op.second))
		arg_2 = op.second;
	else if (op.second == "")
		arg_2 = "";
	else if (!vect.count(op.second))
		throw new exception("Incorrect instructions, please use correct syntax;");
	else
		arg_2 = op.second;
	
	if (oper == operations["input"])
	{
		if (result == "")
			throw new exception("Incorrect instructions, please use correct syntax;");
		
		string base = "";
		string num;
		base = arg_1;
		if (arg_2 == "")
			base = "10";
		else
			base = arg_2;
		
		if (toNumber(base) > 16 || toNumber(base) < 0)
			throw new exception("Incorrect instructions, please use correct syntax;");

		cout << "Input number in base - " << base << ": ";
		cin >> num;

		vect[result] = gorner_in(num, toNumber(base));

		return 0;
	}
	else if (oper == operations["output"])
	{
		//if (result != "")
			//throw new exception("Incorrect instructions, please use correct syntax;");
		if (arg_1 == "")
			throw new exception("Incorrect instructions, please use correct syntax;");

		int base = 10;

		if (arg_2 != "")
			int base = toNumber(arg_2);
	
		cout << arg_1 << " = " << gorner_out(vect[arg_1], base);

		return 0;
	}
	else if (oper == operations["="])
	{
		if (arg_2 == "")
		{
			if (isdigitStr(arg_1))
			{
				vect[result] = toNumber(arg_1);
			}
			else
			{
				if (vect.count(arg_1) && result != "")
				{
					vect[result] = vect[arg_1];
				}
				else
				{
					throw new exception("Incorrect instructions, please use correct syntax;");
				}
			}
		}
		else
		{
			throw new exception("Incorrect instructions, please use correct syntax;");
		}
		
		return 0;
	}
	
	if (arg_2 == "")
		throw new exception("Incorrect instructions, please use correct syntax;");

	int num_1, num_2;

	if (isdigitStr(arg_1))
		num_1 = toNumber(arg_1);
	else
		num_1 = vect[arg_1];

	if (isdigitStr(arg_2))
		num_2 = toNumber(arg_2);
	else
		num_2 = vect[arg_2];

	if (oper == operations["add"])
	{
		vect[result] = num_1 + num_2;
	}
	else if (oper == operations["mult"])
	{
		vect[result] = num_1 * num_2;
	}
	else if (oper == operations["sub"])
	{
		vect[result] = num_1 - num_2;
	}
	else if (oper == operations["pow"])
	{
		vect[result] = pow(num_1, num_2);
	}
	else if (oper == operations["div"])
	{
		vect[result] = num_1 / num_2;
	}
	else if (oper == operations["rem"])
	{
		vect[result] = num_1 % num_2;
	}
	else if (oper == operations["xor"])
	{
		vect[result] = num_1 ^ num_2;
	}
	else
		throw new exception("Incorrect instructions, please use correct syntax;");
}

int Inter::gorner_in(string number, int base)
{
	int flag = 1, j = 0;

	if (number[j] == '-')
	{
		flag = -1;
		++j;
	}

	unsigned long long result = 0;

	for (; j < number.size(); ++j)
		if (isdigit(number[j]))
			result = result * base + (number[j] - '0');
		else
			result = result * base + (number[j] - 'A' + 10);

	return result * flag;
}

string Inter::gorner_out(int num, int base)
{

	unsigned long long number = abs(num);
	int flag = 1;

	if (num < 0)
		flag = -1;

	string bin_num = "";

	if (number)
		while (number)
		{
			char num;

			if (isdigit(number % base + '0'))
				num = (number % base + '0');
			else
				num = (number % base + 'A' + 10);

			bin_num = num + bin_num;
			number /= base;
		}
	else
		bin_num += '0';

	bin_num.reserve();

	if (flag == -1)
		bin_num = '-' + bin_num;

	return bin_num;
}

int Inter::toNumber(string number)
{
	unsigned long long result = 0;

	int i = 0, flag = 1;

	if (number[0] == '-')
	{
		flag = -1;
		++i;
	}

	for (; i < number.size(); ++i)
	{
		result = result * 10 + number[i] - '0';
	}

	return result * flag;
}

Inter::Inter(string file_syntax, string file_instruct)
{
	ifstream file_synt;
	ifstream file_instr(file_instruct);

	if (file_syntax != "")
		file_synt.open(file_syntax);
	else
		file_synt.open("default.txt");

	while (!file_synt.eof())
	{
		string str_inst = "";
		char chr;
		chr = file_synt.get();

		while (chr != '\n' && !file_synt.eof())
		{
			str_inst += chr;
			chr = file_synt.get();
		}

		str_inst = pre_parsing_instruct(str_inst);

		if (str_inst[0] != '\0')
		{
			try
			{
				Inter_Parcer(str_inst);
			}
			catch (exception* ex)
			{
				cout << ex->what() << endl;
				returnToDefault();
				break;
			}
		}
	}

	if (staple_order == Left)
	{
		parser = new Parser_left();
	}
	else if (staple_order == Right)
		parser = new Parser_right();
	else if (staple_order == Left_between)
		parser = new Parser_between();
	else if (staple_order == Right_between)
		parser = new Parser_right_between();

	while (!file_instr.eof())
	{
		string str = "";
		char chr;
		chr = file_instr.get();

		while (chr != ';' && !file_instr.eof())
		{
			str += chr;
			chr = file_instr.get();
		}

		if (file_instr.eof() && chr != -1)
		{
			cout << "Incorrect instructions, please use correct syntax;" << endl;
			break;
		}

		str = pre_parsing(str);

		try
		{
			if (str == "")
				continue;
			Operator_struct op;
			vector<string> args;

			args = split(str, operations["="]);

			if (args.size() == 1)
			{
				op = parser->parse(args[0]);

				op.first = delete_space(op.first);
				if (op.second.size())
					op.second = delete_space(op.second);
				op.op = delete_space(op.op);

				operate(op, "");
			}
			else if (args.size() == 2)
			{
				string result;
				if (left_result)
				{
					result = args[0];
					if (isdigitStr(delete_space(args[1])))
					{
						op.op = operations["="];
						op.first = args[1];
					}
					else
					{
						op = parser->parse(args[1]);
					}
				}
				else
				{
					result = delete_space(args[1]);
					if (isdigitStr(delete_space(args[0])))
					{
						op.op = operations["="];
						op.first = args[0];
					}
					else
					{
						op = parser->parse(args[0]);
					}
				}

				op.first = delete_space(op.first);
				if (op.second.size())
					op.second = delete_space(op.second);
				op.op = delete_space(op.op);
				result = delete_space(result);

				if (op.second.size())
				{
					if (!iscorrect(op.first) || !iscorrect(op.second) || !iscorrect_name(result))
						throw new exception("Incorrect instructions, please use correct syntax;");
				}
				else
					if (!iscorrect(op.first) || !iscorrect_name(result))
						throw new exception("Incorrect instructions, please use correct syntax;");

				operate(op, result);
			}
			else
			{
				throw new exception("Incorrect instructions, please use correct syntax;");
			}
		}
		catch (exception* ex)
		{
			cout << ex->what() << endl;
			break;
		}

	}
}

Inter::~Inter()
{
	ofstream def("default.txt");

	if (left_result)
		def << "left=" << endl;
	else
		def << "right=" << endl;

	if (staple_order == Left)
		def << "op()" << endl;
	else if (staple_order == Right)
		def << "()op" << endl;
	else if (staple_order == Left_between)
		def << "(op)()" << endl;
	else if (staple_order == Right_between)
		def << "()(op)" << endl;

	for (auto it : operations)
	{
		string str = it.first;

		for (int i = 0; i < it.first.size(); ++i)
			def << str[i];
		def << " ";

		str = it.second;

		for (int i = 0; i < it.second.size(); ++i)
			def << str[i];
		def << endl;
	}

	cout << "";
}

void Inter::returnToDefault()
{
	for (auto op : operations)
	{
		operations[op.first] = op.first;
	}

	staple_order = Left;
	left_result = true;
}

void Inter::Inter_Parcer(string syntax)
{
	int i = 0;
	string command = "";

	while (i != syntax.size() && syntax[i] != ' ' && syntax[i] != '\n')
	{
		command += syntax[i];
		++i;
	}

	if (command == "left=")
		left_result = true;
	else if (command == "right=")
		left_result = false;
	else if (command == "op()")
		staple_order = Left;
	else if (command == "()op")
		staple_order = Right;
	else if (command == "(op)()")
		staple_order = Left_between;
	else if (command == "()(op)")
		staple_order = Right_between;
	else if (operations[command].empty())
	{
		cout << "Error syntax" << endl;
		throw new exception("Incorrect syntax, use default settings");
	}
	else
	{
		++i;
		string new_command = "";

		while (syntax[i] != '\0' && syntax[i] != '\n')
		{
			new_command += syntax[i];
			++i;
		}

		operations[command] = new_command;
	}
}

Operator_struct Parser_left::parse(const string op)
{
	Operator_struct operation;
	string comm = "", arg1 = "", arg2 = "";

	int i = 0;

	while (op[i] == ' ')
		++i;

	if (op[i] == '(')
		++i;
	else
		throw new exception("Incorrect syntax, use default settings");

	while (op[i] != ')' && op.size() > i)
	{
		arg1 += op[i];
		++i;
	}

	++i;

	while (op[i] != '(' && op.size() > i)
	{
		comm += op[i];
		++i;
	}

	if (op[i] == '(')
		++i;
	else
		throw new exception("Incorrect syntax, use default settings");

	while (op[i] != ')' && op.size() > i)
	{
		arg2 += op[i];
		++i;
	}
	if (op[i] == ')')
		return Operator_struct{ comm, arg1, arg2 };
	else
		throw new exception("Incorrect syntax, use default settings");
}

Operator_struct Parser_right::parse(const string op)
{
	Operator_struct operation;
	string comm = "", arg1 = "", arg2 = "";

	int i = 0;

	while (op[i] == ' ')
		++i;

	if (op[i] == '(')
		++i;
	else
		throw new exception("Incorrect syntax, use default settings");

	while (op[i] != ',' && op.size() > i)
	{
		arg1 += op[i];
		++i;
	}

	++i;

	while (op[i] != ')' && op.size() > i)
	{
		arg2 += op[i];
		++i;
	}

	if (op[i] != ')')
		throw new exception("Incorrect syntax, use default settings");

	++i;

	while (i < op.size())
	{
		comm += op[i];
		++i;
	}

	return Operator_struct{ comm, arg1, arg2 };
}

Operator_struct Parser_between::parse(const string op)
{
	Operator_struct operation;
	string comm = "", arg1 = "", arg2 = "";

	int i = 0;

	while (op[i] == ' ')
		++i;

	if (op[i] != '(')
	{
		while (op[i] != '(' && op.size() > i)
		{
			comm += op[i];
			++i;
		}
	}

	++i;

	while (op.size() > i && op[i] != ')')
	{
		arg1 += op[i];
		++i;
	}

	if (comm.size() > 0)
	{
		return Operator_struct{ comm, arg1, arg2 };
	}

	if (op[i] == ')')
		++i;
	else
		throw new exception("Incorrect syntax, use default settings");

	while (op[i] != '(' && op.size() > i)
	{
		comm += op[i];
		++i;
	}

	if (op[i] == '(')
		++i;
	else
		return Operator_struct{ comm, arg1, arg2 = "" };

	while (op[i] != ')' && op.size() > i)
	{
		arg2 += op[i];
		++i;
	}
	if (op[i] == ')')
		return Operator_struct{ comm, arg1, arg2 };
	else
		throw new exception("Incorrect syntax, use default settings");

}

Operator_struct Parser_right_between::parse(const string op)
{
	Operator_struct operation;
	string comm = "", arg1 = "", arg2 = "";

	int i = 0;

	while (op[i] == ' ')
		++i;

	if (op[i] != '(')
		throw new exception("Incorrect syntax, use default settings");
	++i;

	while (op[i] != ')' && op.size() > i)
	{
		arg1 += op[i];
		++i;
	}

	if (op[i] == ')')
		++i;
	else
		throw new exception("Incorrect syntax, use default settings");

	while (op[i] != '(' && op.size() > i)
	{
		comm += op[i];
		++i;
	}

	if (op[i] == '(')
		++i;
	else
		return Operator_struct{ comm, arg1, arg2 = "" };

	while (op[i] != ')' && op.size() > i)
	{
		arg2 += op[i];
		++i;
	}
	if (op[i] == ')')
		return Operator_struct{ comm, arg1, arg2 };
	else
		throw new exception("Incorrect syntax, use default settings");

	return Operator_struct();
}
