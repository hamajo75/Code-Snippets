#include <stdio.h>
#include <iostream>
#include <string.h>

class AddHelp
{
	int x = 0;
public:
	AddHelp(int x)
	{
		this->x = x;
	}

	int operator()(int x)
	{
		return this->x + x;
	}

};

class Add
{	
public:	
	AddHelp operator()(int x)
	{
		return AddHelp(x);
	}
};

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{

	std::cout << "\n"
	"Problem:\n"
	"Create an add() function implementing currying\n"
	"add(1)(2)\n\n";

	Add add;
	std::cout << "x + y = " << add(1)(2) << " " << add(3)(4);

	std:cout << "\n";
	system("pause"); 
}
