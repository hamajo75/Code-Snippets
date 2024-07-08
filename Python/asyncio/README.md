# Python asyncio

## Basics
- Event Loop
- Coroutine

## Asynchronous code
Seemingly parallel execution of taks although there is only one thread.
(Parallelism and Concurrency are not the same - tasks might or might not
really run in parallel)

The functions in this context run cooperatively, i.e. they give up execution
voluntarily (`await` keyword).

So the art of writing asynchronous code is about writing nice, well behaved functions
that give up execution and resume at the correct time.

## async functions in Python
- Cannot be simply called, they have to be awaited or passed to the event loop.