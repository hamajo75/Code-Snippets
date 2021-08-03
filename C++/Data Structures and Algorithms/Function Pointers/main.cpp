#include <iostream>
#include <string.h>

typedef int (*myFunPtr_t)(int i);		// this declares a function pointer Type

int myActualFun(int i)
{
	std::cout << "myActualFun called "<< i << "\n";
	return i;
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	myFunPtr_t ptr = myActualFun;
	ptr(1);

	int (*ptr2)(int i) = myActualFun;
	ptr2(2);
	
	std::cout << "\n";
	return 0;
	
}




