#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol
//#include <iostream.h>

//-------------------------------------------------------------------------------
void multiply_arrays(u_int8_t res_arr[], u_int8_t arr1[], int len1, u_int8_t arr2[], int len2)
{
	u_int8_t carry = 0;

	memset(res_arr, 0, len1 + len2);

	for (int i = 0; i < len2; i++)
	{
		int j;
		for (j = 0; j < len1; j++)
		{
			res_arr[j + i] = (arr2[i] * arr1[j] + carry + res_arr[j + i]);
			carry = res_arr[j + i] / 10;
			res_arr[j + i] = res_arr[j + i] % 10; //only keep lower digit
		}
		while (carry)
		{
			res_arr[j + i] = carry + res_arr[j + i];
			carry = res_arr[j + i] / 10;
			res_arr[j + i] = res_arr[j + i] % 10; //only keep lower digit
			j++;
		}
	}
}
//-------------------------------------------------------------------------------
// arr1 = arr2
void assign_array(u_int8_t arr1[], u_int8_t arr2[], int len)
{
	for (int i = 0; i < len; i++)
	{
		arr1[i] = arr2[i];
	}
}
//-------------------------------------------------------------------------------
int int2arr(u_int8_t res_arr[], int n)
{
	int i = 0;
	do
	{
		res_arr[i++] = n % 10;
	}while (n = n / 10);

	return i - 1;
}
//-------------------------------------------------------------------------------
int getNumberOfDecimalPlaces(int n)
{
	int i = 0;
	
	do
	{
		i++;
	}while (n = n / 10);

	return i;
}
//-------------------------------------------------------------------------------
bool calculate_factorial(u_int8_t res_arr[], int len, int n, int len_i)
{	
	if (len_i == 0 || len == 0)
		return false;

	u_int8_t i_arr[len_i] = {0};
	u_int8_t r_arr[len] = {0};	

	int2arr(r_arr, 1);
	for (int i = 2; i <= n; i++)
	{
		int2arr(i_arr, i);

		multiply_arrays(res_arr, i_arr, len_i, r_arr, len);
		assign_array(r_arr, res_arr, len);
	}

	assign_array(r_arr, res_arr, len);
	return true;
}

//-------------------------------------------------------------------------------
void print_arr(u_int8_t arr[], int len)
{
	for (int i = len - 1; i >= 0; i--)
		printf("%d", arr[i]);
}

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	char *p;
	int n;

	errno = 0;
	long conv = strtol(argv[1], &p, 10);

	// Check for errors: e.g., the string does not represent an integer
	// or the integer is larger than int
	if (errno != 0 || *p != '\0' || conv > INT_MAX) 
	{
		printf("Input is not an int!");
	} 
	else 
	{
		// No error
		n = conv;    
		u_int8_t r_arr[1000] = {0};
		if (calculate_factorial(r_arr, 1000, n, getNumberOfDecimalPlaces(n)))
			print_arr(r_arr, sizeof(r_arr)/sizeof(u_int8_t));
		else
			printf("Array size error!");
	    
	}

//	std::cout << "Enter number:\n";
//	std::cin >> n;


	// printf("Enter number: ");
	// scanf("%d", &n);  

	/*	
	u_int8_t arr1[] = {9, 9};
	u_int8_t arr2[] = {9, 9, 9, 9};
	u_int8_t res_arr[8] = {0};

	multiply_arrays(res_arr, arr1, sizeof(arr1)/sizeof(u_int8_t), arr2, sizeof(arr2)/sizeof(u_int8_t));
	print_arr(res_arr, sizeof(res_arr)/sizeof(u_int8_t));
	printf("\n");
	*/

}




