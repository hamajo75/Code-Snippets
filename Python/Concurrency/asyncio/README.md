# Python asyncio

## Basics
- Event Loop
- Coroutine, await
- Generator, yield

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

# alternative:
asyncio.run(my_coroutine())
```

The keyword 'await' is used to pause the execution of the coroutine until the
awaited function is finished.

## Tasks
Calling a coroutine function only creates a coroutine object - nothing runs
until it is awaited or handed to the event loop. A task is a coroutine that has
been scheduled on the event loop: `asyncio.create_task()` schedules it to run
concurrently and returns a handle immediately.

```python
async def main():
    task1 = asyncio.create_task(fetch_data())     # scheduled, runs concurrently
    task2 = asyncio.create_task(print_numbers())

    value = await task1                           # wait for the result of task1
    print(value)
    await task2

asyncio.run(main())
```

Without `create_task`, `await fetch_data()` followed by `await print_numbers()`
runs the two one after the other - the second only starts once the first is
finished. See `create_task.py`.

Common patterns:

```python
# run coroutines concurrently and collect their results, in order
results = await asyncio.gather(fetch_data(), fetch_data())

# same, but the group cancels the remaining tasks if one of them raises (3.11+)
async with asyncio.TaskGroup() as tg:
    t1 = tg.create_task(fetch_data())
    t2 = tg.create_task(print_numbers())

task.cancel()                                      # raises CancelledError in the coroutine
await asyncio.wait_for(fetch_data(), timeout=1.0)  # cancel after a timeout
```

Keep a reference to the tasks you create - the event loop only holds a weak
reference to them, so a task nobody stores or awaits can be garbage collected
while it is still running.

## Generators
Coroutines are a specialized form of generators. So let's briefly mention them here.

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

## Comparing ordinary functions and coroutines
A normal function and a coroutine differ in one core respect: who controls when the body runs.

With a normal function, the call itself runs the body. Control leaves your code, goes into the function, comes back with a value. Nothing else in your program can happen in between.

With a coroutine, the call only creates an object that describes the work. Something else (the event loop) has to drive that object forward. And while it is being driven, it can pause itself at defined points, letting the event loop run other work in the meantime.

Coroutines have to be awaited, or scheduled on the event loop to run. Calling it like a normal function does not run it, it just creates a coroutine object.

```python
async def add(a, b):
    await asyncio.sleep(1)
    return a + b

# Starting the work
async def main():
    x = await add(1, 2)  # await hands control back to the event loop, main suspends until add is done
                         # the value x is returned just like a normal function
    print(x)
```

The `await my_coroutine()` statement is the most similar to a normal function call. But keep in mind that it is also a suspension point.
