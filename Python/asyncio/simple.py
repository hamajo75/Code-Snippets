# coroutines start with "async"
# await: allow other things to be done
# - give execution to other tasks
# - allow the event loop to execute other tasks

import asyncio

async def fetch_data():
  print("start fetching")
  await asyncio.sleep(2)    # this is a time consumint IO-operation
  print("done fetching")
  return {"data": 1}

async def print_numbers():
  for i in range(10):
    print(i)
    await asyncio.sleep(0.25) # non-blocking, standard time.sleep() is blocking!

async def main():
  task1 = asyncio.create_task(fetch_data())
  task2 = asyncio.create_task(print_numbers())

  value = await task1
  print(value)
  await task2

asyncio.run(main())