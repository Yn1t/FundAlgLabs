#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

int gorner_in(string num, int base);

string gorner_out(int number, int base);

int un_op(string op, map<char, int>& vect, char res, int base, string file_name, int& enum_);

int bin_op(map<char, int> & vect, string op, char res, char vector_first, char vector_second, string file_name, int& enum_);

int not_num(int num);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "russian");
	string argv_2;
	bool flag = false;
	ifstream file_in(argv[1]);
	int enum_ = 0;

	if (argv[2])
		argv_2 = argv[2];

	if (argv_2 == "/trace")
	{
		flag = true;
		ofstream file_trace(argv[3]);
	}

	map<char, int> vect;

	while (file_in)
	{
		string str = "";
		int i = 0;
		char chr = '\0';

		file_in >> chr;

		if (chr == '\0')
			break;

		while (chr != ';' && file_in)
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


		while (str[i] != ':' && str[i] != '(' && str[i] != '\n')
		{
			if (i == 0)
				if (str[i] >= 'A' && str[i] <= 'Z')
				{
					res = str[i];
					i++;
					break;
				}
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
				op += 'e';
			else
			{
				printf("Error");
				return -1;
			}
			++i;
		}

		if (op.length() != i && op.length() != 0)
		{
			cout << "Error" << endl;
			return -1;
		}

		if (op.length())
		{
			int base;
			if (str[i] != '(')
			{
				cout << "Error" << endl;
				return -1;
			}

			++i;

			if (str[i] < 'A' || str[i] > 'Z')
			{
				cout << "Error" << endl;
				return -1;
			}

			res = str[i];
			++i;

			if (str[i] != ',')
			{
				cout << "Error" << endl;
				return -1;
			}

			++i;

			if (isdigit(str[i]) && (isdigit(str[i + 1]) || str[i + 1] == ')'))
			{
				if (isdigit(str[i + 1]))
				{
					base = (str[i] - '0') * 10 + (str[i + 1] - '0');
					i++;
				}
				else
					base = str[i] - '0';
				++i;
			}
			else
			{
				cout << "Error" << endl;
				return -1;
			}

			if (str[i] != ')')
			{
				cout << "Error" << endl;
				return -1;
			}

			if (str.size() - 1 != i)
			{
				cout << "Error" << endl;
				return -1;
			}

			if (flag)
			{
				if (un_op(op, vect, res, base, argv[3], enum_) == -1)
					return -1;
			}
			else
			{
				if (un_op(op, vect, res, base, "", enum_) == -1)
					return -1;
			}
		}
		else if (str[i] == ':')
		{
			++i;

			if (str[i] != '=')
			{
				cout << "Error" << endl;
				return -1;
			}
			++i;

			if (str[i] == '\\')
			{
				++i;
				if (str[i] < 'A' || str[i] > 'Z')
				{
					cout << "Error" << endl;
					return -1;
				}

				char second_vect = str[i];
				op += '\\';

				if (str.size() - 1 != i)
				{
					cout << "Error" << endl;
					return -1;
				}

				if (flag)
				{
					if (un_op(op, vect, res, second_vect, argv[3], enum_) == -1)
						return -1;
				}
				else
				{
					if (un_op(op, vect, res, second_vect, "", enum_) == -1)
						return -1;
				}
			}
			else if (str[i] >= 'A' && str[i] <= 'Z')
			{
				char vector_first, vector_second;
				vector_first = str[i];
				++i;
				if (str.size() == i)
				{
					op += "=";

					if (flag)
					{
						if (un_op(op, vect, res, vector_first, argv[3], enum_) == -1)
							return -1;
					}
					else
					{
						if (un_op(op, vect, res, vector_first, "", enum_) == -1)
							return -1;
					}
				}
				else
				{
					if (str[i] == '+')
					{
						if (str[i + 1] >= 'A' && str[i + 1] <= 'Z')
							op += "+";
						else if (str[i + 1] == '>')
						{
							op += "+>";
							++i;
						}
						else
						{
							cout << "Error" << endl;
							return -1;
						}
					}
					else if (str[i] == '&')
						op += '&';
					else if (str[i] == '-')
					{
						++i;
						if (str[i] == '>')
							op += "->";
						else
						{
							cout << "Error" << endl;
							return -1;
						}
					}
					else if (str[i] == '<')
					{
						++i;
						if (str[i] == '-')
							op += "<-";
						else if (str[i] == '>')
							op += "<>";
						else
						{
							cout << "Error" << endl;
							return -1;
						}
					}
					else if (str[i] == '~')
					{
						op += '~';
					}
					else if (str[i] == '?')
					{
						op += '?';
					}
					else if (str[i] == '!')
					{
						op += '!';
					}
					else
					{
						cout << "Error" << endl;
						return -1;
					}
					++i;

					if (str[i] < 'A' || str[i] > 'Z')
					{
						cout << "Error" << endl;
						return -1;
					}

					vector_second = str[i];
					++i;

					if (str.size() != i)
					{
						cout << "Error" << endl;
						return -1;
					}

					if (flag)
					{
						if (bin_op(vect, op, res, vector_first, vector_second, argv[3], enum_) == -1)
						{
							cout << "Error" << endl;
							return -1;
						}
					}
					else
					{
						if (bin_op(vect, op, res, vector_first, vector_second, "", enum_) == -1)
						{
							cout << "Error" << endl;
							return -1;
						}
					}
				}

			}
			else
			{
				cout << "Error" << endl;
				return -1;
			}
			++i;
		}
		else if (str[i] == '\n')
		{
			break;
		}
		else
		{
			cout << "Error" << endl;
			return -1;
		}
	}
}

int gorner_in(string number, int base)
{
	int result = 0;

	for (int j = 0; j < number.size(); ++j)
		if (isdigit(number[j]))
			result = result * base + (number[j] - '0');
		else
			result = result * base + (number[j] - 'A' + 10);

	/*string bin_num = "";

	while (result)
	{
		char num = (result % 2+ '0');
		bin_num = num + bin_num;
		result /= 2;
	}

	bin_num.reserve();*/

	return result;
}

string gorner_out(int number, int base)
{
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

	return bin_num;
}

int un_op(string op, map<char, int>& vect, char res, int base, string file_name, int& enum_)
{
	string str;

	if (file_name.size())
	{
		ofstream file_trace(file_name, ios::app);
		file_trace << enum_ << ": ";
		enum_++;
	}

	if (op == "read")
	{
		string num;
		cout << res << ":=";
		cin >> num;

		vect.insert({ res, gorner_in(num, base) });

		if (file_name.size())
		{
			ofstream file_trace(file_name, ios::app);
			file_trace << "¬ вектор " << res << " записано значение - " << num << " - в системе счислени€ - " << base << endl;
		}

	}
	else if (op == "write")
	{
		if (vect.count(res))
		{
			cout << res << " = " << gorner_out(vect[res], base) << " в системе счислени€ " << base << endl;
		}
		else
			cout << "Ќет вектора с таким именем;" << endl;

		if (file_name.size())
		{
			ofstream file_trace(file_name, ios::app);
			file_trace << "¬ консоль выведен вектор " << res << " в системе счислени€ - " << base << " = " << vect[res] << ";" << endl;
		}
	}
	else if (op == "\\")
	{
		char second_vect = base;

		if (vect.count(res) && vect.count(second_vect))
		{
			vect[res] = not_num(vect[second_vect]);
		}
		else
		{
			cout << "Ќет вектора с таким именем;" << endl;
			return -1;
		}

		if (file_name.size())
		{
			ofstream file_trace(file_name, ios::app);
			file_trace << "ѕроизведена операци€ логического отрицани€ над вектором " << second_vect << " и присвоена вектору " << res << " = "\
				<< vect[res] << endl;
		}
	}
	else if (op == "=")
	{
		char second_vect = base;

		if (vect.count(res) && vect.count(second_vect))
		{
			vect[res] = vect[second_vect];
		}
		else
		{
			cout << "Ќет вектора с таким именем;" << endl;
			return -1;
		}

		if (file_name.size())
		{
			ofstream file_trace(file_name, ios::app);
			file_trace << "ѕроизведена операци€ присваивани€ вектору " << second_vect << " значени€ вектора " << res << endl;
		}
	}
	else
	{
		cout << "Error" << endl;
		return -1;
	}

}

int bin_op(map<char, int>& vect, string op, char res, char vector_first, char vector_second, string file_name, int& enum_)
{
	if (file_name.size())
	{
		ofstream file_trace(file_name, ios::app);
		file_trace << enum_ << ": "<< "ѕроизведена операци€ " << op << " с векторами " << \
			vector_first << " и " << vector_second << ", результат присвоен " << res;
		enum_++;
	}

	if (!(vect.count(res) && vect.count(vector_first) && vect.count(vector_second)))
	{
		cout << "Ќет вектора с таким именем;" << endl;
		return -1;
	}

	if (op == "+")
	{
		vect[res] = vect[vector_first] | vect[vector_second];
	}
	else if (op == "&")
	{
		vect[res] = vect[vector_first] & vect[vector_second];
	}
	else if (op == "->")
	{
		vect[res] = not_num(vect[vector_first]) | vect[vector_second];
	}
	else if (op == "<-")
	{
		vect[res] = not_num(vect[vector_second]) | vect[vector_first];
	}
	else if (op == "~")
	{
		vect[res] = (not_num(vect[vector_first]) & not_num(vect[vector_second])) | (vect[vector_first] & vect[vector_second]);
	}
	else if (op == "<>")
	{
		vect[res] = vect[vector_first] ^ vect[vector_second];
	}
	else if (op == "+>")
	{
		vect[res] = not_num((not_num(vect[vector_first])) | vect[vector_second]);
	}
	else if (op == "?")
	{
		vect[res] = not_num(vect[vector_first] & vect[vector_second]);
	}
	else if (op == "!")
	{
		vect[res] = not_num(vect[vector_first] | vect[vector_second]);
	}

	if (file_name.size())
	{
		ofstream file_trace(file_name, ios::app);
		file_trace << " = " << vect[res] << endl;
	}

	return 0;
}

int not_num(int num)
{
	int i = (1 << (1 + (int)(log(num) * (1 / log(2))))) - 1;
	return (i ^ num);
}
