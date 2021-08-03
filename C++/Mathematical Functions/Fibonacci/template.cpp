#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

//-------------------------------------------------------------------------------
// This is of course not a good solution because many calculations are done
// multiple times (See the picture). 
//-------------------------------------------------------------------------------
int fibonacci(int n)
{
    if ((n == 1) || (n == 2))
    {
        return 1;
    }
    
    return (fibonacci(n-1) + fibonacci(n-2));
}    
//-------------------------------------------------------------------------------
std::map<long, long> memo;          // memoization
long fibonacci_improved(int n)
{
    if (memo.find(n) != memo.end()) 
        return memo[n];

    if ((n == 1) || (n == 2))
    {
        return 1;
    }
    
    memo.insert({n, (fibonacci_improved(n-1) + fibonacci_improved(n-2))});
    return memo[n];
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	int input;
	std::cout <<"Input: "; std::cin >> input;
    std::cout << "Output: " << fibonacci_improved(input) << "\n";   

    std::cout << "Output: " << fibonacci_improved(50) << "\n";   // returns instantly
    std::cout << "Output: " << fibonacci(50) << "\n";            // takes forever
}




