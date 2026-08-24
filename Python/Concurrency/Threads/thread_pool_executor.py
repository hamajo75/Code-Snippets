#!/usr/bin/env python3

from concurrent.futures import ThreadPoolExecutor
from time import sleep


def fetch_value(value):
    """Simulate work performed by a worker thread."""
    sleep(0.5)
    return value * 2


def main():
    values = [1, 2, 3, 4]

    # The executor creates and manages the worker threads.
    with ThreadPoolExecutor(max_workers=3) as executor:
        futures = [executor.submit(fetch_value, value) for value in values]

        for value, future in zip(values, futures):
            print(f"{value} -> {future.result()}")


if __name__ == "__main__":
    main()
