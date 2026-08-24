import asyncio


def connect(modem):
    # Simulate a blocking network connection
    print(f"Connecting to {modem}")
    import time
    time.sleep(5)
    print(f"Connected to {modem}")
    return f"Connection to {modem} established"


async def call_blocking_function():
    loop = asyncio.get_running_loop()
    result = await loop.run_in_executor(None, connect, "modem")
    print(result)


async def main():
    await call_blocking_function()


if __name__ == '__main__':
    asyncio.run(main())
