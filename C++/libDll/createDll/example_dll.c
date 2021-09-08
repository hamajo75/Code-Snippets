#include <stdio.h>

extern __declspec(dllexport) int __stdcall call(char *data, int size)
{
	printf("%s, data size: %d\n\n", data, size);

	return size;
}