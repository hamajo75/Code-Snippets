#include <windows.h>
#include <stdio.h>

typedef int (__stdcall *call_ptr)(char *data, int size);

call_ptr call;

int main(void)
{
	printf("start\n");

	HINSTANCE handle = LoadLibrary(TEXT("example_dll.dll"));
	if (handle)
	{
		printf("library successfully loaded\n");
		call = (call_ptr)GetProcAddress(handle, "call");

		char *data = "hello dll";
		int ret = call(data, sizeof(data)/sizeof(char));
		printf("return value: %d\n\n", ret);
	}
	else
	{
		printf("can not load library\n\n");
		return -1;
	}

	return 0;
}