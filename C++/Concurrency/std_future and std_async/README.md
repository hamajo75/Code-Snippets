# std::future and std::async

## Introduction
`std::async` (C++11, header `<future>`) runs a callable asynchronously and returns a `std::future` that will hold its result.
It is the simplest way to start a task and collect its result later, without creating and joining a `std::thread` by hand.

```cpp
std::future<int> f = std::async(std::launch::async, [] { return 42; });
// ... do other work ...
int result = f.get();   // blocks until the result is available
```

Any callable can be used: a function, a function object or a lambda. Additional arguments to `std::async` are passed on to the callable (by value, like with `std::thread`).

## std::future
A `std::future<T>` is the receiving end of a one-shot channel. The producer (here `std::async`) stores either a value or an exception in a shared state, and the future reads it.

- `get()`: Wait for the result and return it. If the task threw an exception, `get()` rethrows it. Can only be called **once**; afterwards the future is no longer valid.
- `wait()`: Wait for the result without retrieving it.
- `wait_for(duration)` / `wait_until(time_point)`: Wait with a timeout. Returns `std::future_status::ready`, `timeout` or `deferred`.
- `valid()`: `true` if the future refers to a shared state (i.e. `get()` has not been called yet).
- `share()`: Convert into a `std::shared_future`, which can be copied and whose `get()` can be called multiple times, e.g. to let several threads wait for the same result.

A `std::future` is move-only.

## Launch Policies
The first, optional argument of `std::async` is the launch policy:
- `std::launch::async`: Run the task on a new thread right away.
- `std::launch::deferred`: Don't start a thread. The task is run lazily in the calling thread, when `get()` or `wait()` is called on the future.
- `std::launch::async | std::launch::deferred`: The default if no policy is given. The implementation chooses.

Because the default policy may defer the task, it is not guaranteed that the task runs in parallel at all (or ever, if `get()` is never called).
Pass `std::launch::async` explicitly if real concurrency is needed.

## Pitfalls
- The destructor of a future returned by `std::async` **blocks** until the task is finished. Discarding the return value therefore makes the call synchronous:
  ```cpp
  std::async(std::launch::async, task1);  // temporary future is destroyed here -> waits
  std::async(std::launch::async, task2);  // only starts after task1 is done
  ```
  Keep the futures in variables to really run the tasks concurrently.
- `get()` may only be called once. Use `std::shared_future` if the result is needed more than once.
- `wait_for()` on a deferred task returns `std::future_status::deferred` immediately, so a polling loop on `ready` would never end.

## std::async vs. std::thread vs. std::promise
- `std::thread`: No direct way to return a value, exceptions terminate the program, must be joined or detached.
- `std::async`: Returns the result (or exception) through a future, no explicit join needed.
- `std::promise`: The manual producer side of a future. Use it when the value is set by code that is not a simple function return, e.g. from inside a running thread or a callback. See `../std_future and std_promise`.
