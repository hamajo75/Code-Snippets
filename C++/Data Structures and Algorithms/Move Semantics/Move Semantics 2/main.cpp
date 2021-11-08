#include <iostream>
#include <string.h>

class MyClass
{
public:
	int* Data;
	uint32_t Size;

	MyClass(uint32_t size)
	{
		std::cout << "MyClass object constructed\n";
		Size = size;
		Data = new int[Size];
	}
	MyClass(const MyClass& other)
	{
		Size = other.Size;
		Data = new int[Size];		
		memcpy(Data, other.Data, other.Size);

		std::cout << "MyClass object copied\n";
	}	
	MyClass(MyClass&& other)
	{
		Size = other.Size;
		Data = other.Data;		
		
		other.Size = 0;									// !! very important, otherwise other's Destructor could kill our Data !!
		other.Data = nullptr;

		std::cout << "MyClass object moved\n";
	}
	~MyClass()
	{
		std::cout << "MyClass object destroyed\n";
	}
};

class MyOtherClass
{
private:
	MyClass Data;	
public: 
	MyOtherClass(const MyClass& data)	
		: Data(data)
	{}
	MyOtherClass(MyClass&& data)	
		: Data(std::move(data))
	{}	
};
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	//int* a = std::move(myMoveFun());
	MyOtherClass oobj(MyClass(1000));

	std::cout << "\n";
	return 0;
	
}
//-------------------------------------------------------------------------------
// int* myMoveFun()
// {
// 	int a[1000] = {0};
// 	return a;
// }



