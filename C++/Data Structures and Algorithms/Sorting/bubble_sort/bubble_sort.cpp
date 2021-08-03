#include <iostream>
#include <stdio.h>

/*
int arr[]
is the same as:
int* arr
 */

void swap(int arr[], int i, int j)
{
	int n = arr[i];
	arr[i] = arr[j];
	arr[j] = n;
}

/*
inner loop has the moving element
|= no confusion in the swap case
*/
void sort(int arr[], int len)
{
	for(int i = 1; i < len; i++)
	{
		for(int j = 0; j < len - i; j++)
		{
			if (arr[j] > arr[i])
				swap(arr, i, j);
		}
	}
}


/*
this works also
important: j = i + 1 (otherwise endless loop)
 */
void sort_stupid(int arr[], int len)
{
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = i + 1; j < len; j++)
		{
			if (arr[i] > arr[j])
				swap(arr, i, j);
		}
	}
}


int main(int argc, const char* argv[])
{
	std::cout << "Bubble Sort\n";

	const int len = 10;
	int arr[len] = {5, 1, 6, 2, 9, 3, 4, 7, 8, 0};
	sort(arr, len);

	for (int i = 0; i < len; i++)
		//		std::cout << arr[i];
		printf("%d ", arr[i]);
}
