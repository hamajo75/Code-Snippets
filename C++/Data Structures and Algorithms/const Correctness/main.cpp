#include <iostream>
#include <string.h>

class Entity
{
private:
	int m_X;
	int* m_Y;	
	mutable int var = 1;	// allow the const getX() function to change this variable
public:
	Entity(int x, int* y)
	{
		m_X = x;
		m_Y = y;
	}

	int getX() const		// inside a class, this method cannot change the member
	{
		var = 2;
		return m_X;
	}	
	int* getY() const	// return a const pointer to something that is const and this method cannot change the pointer
	{
		return m_Y;
	}
	void setY(int* y)
	{

	}
	void setX(int x)
	{

	}
};
//-------------------------------------------------------------------------------
void PrintEntity(const Entity& e)		// to use the const reference (to avoid copying) getX() has to be const otherwise there is a compile error
{
	//e = nullptr;
	std::cout << "Entity: " << e.getX() << "\n";
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	int i = 0;
	int u = 1;
	const Entity e(1, &i);

	//e.setX(1);
	//e.setY(&u);
	*e.getY() = 2;
	std::cout << i;

	const int MAX_NR_OF_CHARS = 1;
	// MAX_NR_OF_CHARS = 2;			// compile error
	
	// int* p_int = new int;
	const int* p_int = &MAX_NR_OF_CHARS; 	// ptr to const int
	//*p_int = 2;
	// p_int = (int*)&MAX_NR_OF_CHARS;		// this compiles

	int* const p_int2 = new int;		// const ptr to int
	// p_int2++;						// compile error
	*p_int2 =  3;						// thats ok, only the pointer is const

	return 0;
}




