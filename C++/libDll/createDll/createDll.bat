gcc -c -DBUILDING_EXAMPLE_DLL example_dll.c
gcc -shared -o example_dll.dll example_dll.o -Wl,--out-implib,libexample_dll.a
pause
