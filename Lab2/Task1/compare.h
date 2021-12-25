#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

template <class T>
class Compare
{
public:
	virtual int compare(const T& left, const T& right) const = 0;
	virtual ~Compare() {};
};

class CompareInt : public Compare <int>
{
public:
	int compare(const int& left, const int& right) const override
	{
		if (left > right)
			return 1;
		else if (left == right)
			return 0;
		else
			return -1;
	};
};

class CompareStr : public Compare <string>
{
public:
	int compare(const string& left, const string& right) const override
	{
		if (left.length() == right.length())
		{
			if (left > right)
				return -1;
			else if (left < right)
				return 1;
			else
				return 0;
		}
		else if (left.length() > right.length())
			return 1;
		else
			return -1;
	};
};

class CompareVector : public Compare <vector<int>>
{
public:
	int compare(const vector<int>& left, const vector<int>& right) const
	{
		if (left.size() > right.size())
			return 1;
		else if (left.size() < right.size())
			return -1;
		else
		{
			int left_average = 0, right_average = 0;
			for (int i = 0; i < left.size(); ++i)
				left_average += left[i];

			for (int i = 0; i < right.size(); ++i)
				right_average += right[i];

			if (left_average > right_average)
				return 1;
			else if (left_average < right_average)
				return -1;
			else
				return 0;
		}
	};
};