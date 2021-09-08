#include <iostream>
#include <string>
#include <memory>
/*
With C++11, everything can be initialized in much the same way.
*/
//-------------------------------------------------------------------------------
// Initialization of a C-Array as attribute of a class
//-------------------------------------------------------------------------------
class Array
{
public:
    int myData[5];
    Array(): myData{1,2,3,4,5}{}    
};
//-------------------------------------------------------------------------------
class Point
{
public:
    int x; 
    int y; 
};
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
    // initialization using attributes (not the constructor)
    Point point = {1, 2};   // copy initialization
    Point point2 {1, 2};     // direct initialization
    std::cout << "x: " << point.x << " y: " << point.y << "\n";

    Array my_array; // initializes a int array in the constructor

    for (auto element: my_array.myData)
        std::cout << element << " \n";

    // Initialization of a const array on the heap
    const int* data= new const int[3]{1, 2, 3};

    // with auto in combination with a {}-initialization, we will get an std::initializer_list in C++14

    std::cout << "\n";
    return 0;
}




