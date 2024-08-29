# coroutines start with "async"
# await: allow other things to be done
# - give execution to other tasks
# - allow the event loop to execute other tasks

import asyncio


async def fetch_data():
    print("start fetching")
    await asyncio.sleep(2)    # this is a time consuming IO-operation, give back control to the event loop
    print("done fetching")
    return {"data": 1}


async def print_numbers():
    for i in range(10):
        print(i)
        # non-blocking, standard time.sleep() is blocking!
        await asyncio.sleep(0.25)


async def main():
    task1 = asyncio.create_task(fetch_data())
    task2 = asyncio.create_task(print_numbers())

    value = await task1
    print(value)
    await task2

asyncio.run(main())
