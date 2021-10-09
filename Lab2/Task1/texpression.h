#pragma once

#include <exception>
using namespace std;

class TreeException : public exception
{

};

class TreeExceptionNonExisted : public TreeException
{
public:
	const char* what() const override;
};

class TreeExceptionIsExisted : public TreeException
{
public:
	const char* what() const override;
};

class TreeExceptionCompErr : public TreeException
{
public:
	const char* what() const override;
};

class ExceptionIndexErr : public TreeException
{
public:
	const char* what() const override;
};

class ExceptionTreeIsNotExist : public TreeException
{
public:
	const char* what() const override;
};

const char* ExceptionTreeIsNotExist::what() const
{
	return "This tree is not exist;\n";
}

const char* ExceptionIndexErr::what() const
{
	return "This index it too large;\n";
}

const char* TreeExceptionNonExisted::what() const
{
	return "This key isn't exist;\n";
}

const char* TreeExceptionIsExisted::what() const
{
	return "This key is already exist;\n";
}

const char* TreeExceptionCompErr::what() const
{
	return "Comparator error;\n";
}
