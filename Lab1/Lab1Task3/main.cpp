#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stdarg.h"

double solution_pol(double x, int degree, ...);

int main()
{
	std::cout << solution_pol(3.0, 2, 1.0, 2.0, 1.0) << std::endl;
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