#include <iostream>
#include <list>
#include <fstream> 
using namespace std;

#define HASHSIZE 128

class Hash_table {
	struct node {
		string key;
		string value;
	};
public:
	list<node> Nodes[HASHSIZE];
	Hash_table() {};
	int get_rem(string def_name);
	string find(string def_name);
	void insert(string def_name, string def_value);
};

int main()
{
	ifstream file_in("file_in.txt");
	ofstream file_out("file_out.txt");

	Hash_table hash;

	char chr;
	file_in >> chr;

	while (chr == '#')
	{
		string def_name = "", def_value = "";

		for (int i = 0; i < 7; ++i)
			chr = file_in.get();

		file_in >> chr;

		while (chr != ' ')
		{
			def_name += chr;
			chr = file_in.get();
		}

		file_in >> chr;

		while (chr != '\n')
		{
			def_value += chr;
			chr = file_in.get();
		}

		chr = file_in.get();

		hash.insert(def_name, def_value);
	}

	string word = "";

	while (chr != ' ')
	{
		word += chr;
		chr = file_in.get();
	}

	while (file_in)
	{
		//chr = file_in.get();

		file_out << hash.find(word);

		file_out << ' ';

		//word = "";

		file_in >> word;

		chr = file_in.get();
	}

	return 0;
}

int Hash_table::get_rem(string def_name)
{
	unsigned long long result = 0;
	int base = 62;

	for (auto s : def_name)
	{
		if (isdigit(s))
			result = result * base + (s - '0');
		else if (s <= 'Z')
			result = result * base + (s - 'A' + 10);
		else
			result = result * base + (s - 'a' + 36);
	}

	int rem = result % HASHSIZE;

	return rem;
}

string Hash_table::find(string def_name)
{
	int rem = get_rem(def_name);

	for (auto it : Nodes[rem])
		if (it.key == def_name)
			return it.value;

	return def_name;
}

void Hash_table::insert(string def_name, string def_value)
{
	int rem = get_rem(def_name);

	this->Nodes[rem].push_back({ def_name, def_value });
}
