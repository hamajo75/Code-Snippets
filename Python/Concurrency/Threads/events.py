#!/usr/bin/env python3

import threading
import time

# Event acts like a shared boolean flag between threads
event = threading.Event()

# This event will be used to stop a worker thread cleanly
stop_event = threading.Event()


def worker():
    """
    Worker thread that:
    1. Waits for a "start signal" (event)
    2. Runs work in a loop
    3. Stops when stop_event is set
    """

    print("[worker] Started, waiting for start signal...")

    # Blocks here until event.set() is called
    event.wait()
    print("[worker] Received start signal, beginning work!")

    counter = 0

    # Runs until stop_event is set
    while not stop_event.is_set():
        counter += 1
        print(f"[worker] working... step {counter}")
        time.sleep(1)

    print("[worker] Stop signal received, cleaning up...")


def monitor():
    """
    Second thread that waits with timeout and reacts.
    Demonstrates timeout + is_set() check.
    """

    print("[monitor] Waiting for event with timeout...")

    # Wait up to 3 seconds for event
    if event.wait(timeout=3):
        print("[monitor] Event was set in time!")
    else:
        print("[monitor] Timeout reached, event not set yet")

    # Check state without blocking
    if event.is_set():
        print("[monitor] Event is currently set")
    else:
        print("[monitor] Event is still not set")


# -------------------------
# MAIN THREAD (controller)
# -------------------------

# Start worker thread (it will block on event.wait())
t = threading.Thread(target=worker)
t.start()

# Start monitor thread (shows timeout behavior)
m = threading.Thread(target=monitor)
m.start()

# Simulate some setup time
time.sleep(2)

print("[main] Setting event -> worker can start now")
event.set()   # Releases worker + monitor wait()

# Show that wait() now returns immediately
print("[main] event.is_set() =", event.is_set())

# Let worker run for a few seconds
time.sleep(4)

print("[main] Stopping worker using stop_event")
stop_event.set()

# Wait for threads to finish
t.join()
m.join()

print("[main] Done")
