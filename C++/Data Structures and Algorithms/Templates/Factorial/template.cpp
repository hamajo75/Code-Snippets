#include <stdio.h>
#include <iostream>
#include <string.h>

// class MyType
// {
// private:
// 	u_int8_t array[1000] = {0};
// 	uint length = 0;
// 
// public:
// 	MyType(const int n)
// 	{
// 		int i = 0;
// 		do
// 		{
// 			array[i++] = n % 10;
// 		}while (n = n / 10);
// 
// 		this->length = i;
// 	}
// 
// 	std::string getValue() const
// 	{
// 		std::string	value; 
// 		for (int i = this->length - 1; i >= 0; i--)
// 			value.push_back((char)array[i]);
// 		return value;			
// 	}
// 
// 	uint length()
// 	{
// 		return length;
// 	}
// 
// 	MyType operator*(const MyType& value)
// 	{
// 		MyType res;
// 
// 		for (int i = 0; i < value.length(); i++)
// 		{
// 			int j;
// 			for (j = 0; j < this->length(); j++)
// 			{
// 				res_arr[j + i] = (arr2[i] * arr1[j] + carry + res_arr[j + i]);
// 				carry = res_arr[j + i] / 10;
// 				res_arr[j + i] = res_arr[j + i] % 10; //only keep lower digit
// 			}
// 			while (carry)
// 			{
// 				res_arr[j + i] = carry + res_arr[j + i];
// 				carry = res_arr[j + i] / 10;
// 				res_arr[j + i] = res_arr[j + i] % 10; //only keep lower digit
// 				j++;
// 			}
// 		}	
// 
// 		return MyType(this->getValue() * value.getValue());
// 	}	
// };

//-------------------------------------------------------------------------------
template <typename T>
T factorial(const int n)
{
	if (n == 1)
		return 1;
	else
		return T(n) * factorial<T>(n - 1);
}

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	int n;
	std::cout << "Enter n: ";
	std::cin >> n;
	
   std::cout << "Result: " << factorial<long>(n);
}




