#include <stdio.h>
#include <iostream>
#include <string.h>

/*
Problem:

You need 3 functions that use the same parts.
fun1    fun2   fun3 
A       A      B
B       D      C
C       C      A

You can do that of course by implementing A, B, C, D as functions.
But what if there are many local variables around and you don't
want a lot of parameters.

You might want to implement A, B, C, D inside a class.

*/

struct Fun
{
	const static int context = 1;
	int A(){return context + 1;}
	int B(){return context + 2;}
	int C(){return context + 3;}
	int D(){return context + 4;}
};

struct Fun1 : public Fun
{
	int operator()()
	{
		return A() + B() + C();
	}
};
struct Fun2 : public Fun
{
	int operator()()
	{
		return A() + D() + C();
	}
};
struct Fun3 : public Fun
{
	int operator()()
	{
		return B() + C() + A();
	}
};

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{

	Fun1 fun1;
	Fun2 fun2;
	Fun3 fun3;
	
	std::cout << "fun1: " << fun1() << " fun2: " << fun2() << " fun3: " << fun3();

}




