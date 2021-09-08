#include <iostream>
#include <string.h>
#include <vector>
#include <utility>

class String
{
private: 
	char* m_Data;
	uint32_t m_Size;

public: 
	String() = default;
	String(const char* string)
	{
		std::cout << "String created!\n";
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}	
	String(const String& other)
	{
		std::cout << "String copied!\n";
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}

	~String() { delete m_Data; }
};

class Entity
{
private:
	String m_Name;	
public: 
	Entity(const String& name)
		: m_Name(name)
	{
		
	}
};
//-------------------------------------------------------------------------------
template <typename T>
void print(T v)
{
	std::cout << "Elements: ";

	for(auto e: v)
		std::cout << e << " ";

	std::cout << "\n";
}

void printIntVector(std::vector<int> v)
{
	print<std::vector<int>>(v);
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	//Entity e;

	std::vector<int> v1 = {1, 2, 3, 4};	 // resource handle, container 	
	std::vector<int> v2 = {5, 6, 7, 8};		

	printIntVector(v1);
	printIntVector(v2);

	v2 = std::move(v1);				// now v1 is empty

	printIntVector(v1);
	printIntVector(v2);

	auto v3 = std::move(v2);		// now v2 is empty

	printIntVector(v1);
	printIntVector(v2);
	printIntVector(v3);

	return 0;
}




