# Python asyncio

## Basics
- Event Loop
- Coroutine
- Generator
- await

## Asynchronous code
Seemingly parallel execution of tasks although there is only one thread.
(Parallelism and Concurrency are not the same - tasks might or might not
really run in parallel).

The functions in this context run cooperatively, i.e. they give up execution
voluntarily (`await` keyword). AsyncIO is a single-threaded,
single-process design: it uses cooperative multitasking.

So the art of writing asynchronous code is about writing nice, well behaved functions
that give up execution and resume at the correct time.

## Coroutines
Coroutines are a type of function that can pause their execution before reaching return,
and they can indirectly pass control back to the event loop, allowing other tasks to run.

Here is a simple example of a coroutine in Python:

```python
async def my_coroutine():
    print("Coroutine started")
    await asyncio.sleep(1)
    print("Coroutine resumed")

# To run the coroutine, we need to create an event loop and schedule the coroutine to run
loop = asyncio.get_event_loop()
loop.run_until_complete(my_coroutine())

# alertenative:
asyncio.run(my_coroutine())
```

The keyword 'await' is used to pause the execution of the coroutine until the
awaited function is finished.

## Generators
Generators are a type of function that allow you to create a sequence of values.
They are defined with def and use the yield statement to produce a series of values lazily,
meaning values are computed as needed rather than all at once.

```python
def generator_example():
    yield 1
    yield 2
    yield 3

for value in generator_example():
    print(value)

```

## async functions in Python
- Cannot be simply called, they have to be awaited or passed to the event loop.