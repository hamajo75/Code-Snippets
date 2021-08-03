#include <iostream>
#include <string.h>
#include <vector>

//-------------------------------------------------------------------------------
void printVector(const std::vector<int>& v)
{
	for (const auto& e : v)
		std::cout << e << " ";

	std::cout << "\n";
}
//-------------------------------------------------------------------------------
void swap(std::vector<int>& v, const int i, const int j)
{
	int z = v[i];
	v[i] = v[j];
	v[j] = z;
}
void sort(std::vector<int>& v)
{

}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	std::vector<int> v = {5, 3, 1, 1, 7, 4};
	sort(v);
	//swap(v, 0, 1);
	printVector(v);

	return 0;
	
}




