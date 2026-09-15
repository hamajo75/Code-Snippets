# Concurrency in Python

## Global Interpreter Lock (GIL)
Prevents the parallel execution of bytecode in the same process. I.e. only
one thread at a time can be running (even if there are multiple cores). This is
true for CPU bound operations. For I/O bound operations, the GIL is released when waiting for I/O.
