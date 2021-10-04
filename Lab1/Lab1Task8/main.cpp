#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class H
{
	int sum(const H&, int, int);
	int _xor(const H&, int, int);
	vector<function<int(const H&, int, int)>> funcs{ sum, _xor };

};

int main()
{
	return 0;
}