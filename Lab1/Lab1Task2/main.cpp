#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stdarg.h"
using namespace std;

typedef struct {
	double x;
	double y;
} point;

bool is_convex(int count, ...);

int main()
{
	setlocale(LC_ALL, "russian");
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