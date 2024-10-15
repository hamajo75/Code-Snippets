# C++ Coroutines

## Introduction
This is a new feature in C++20.

A coroutine is essentially a function that can suspend its execution to be resumed later, maintaining its state in between.
Because it can suspend the return value of the coroutine has to contain a handle to the coroutine in order to resume it later.

The related new keywords are
- `co_await`: Suspend the coroutine until the awaited asynchronous task is complete .
- `co_yield`: Suspend the coroutine and return a value to the caller. Resume at same point when called again.
- `co_return`: Signal the end of the coroutine and return final value to the caller.

There is not extra syntactic keyword to define a coroutine, it is just a function that uses the above keywords.

A coroutine returns an object that acts as the coroutine interface for the caller. In C++ 20 this object has to be provided by the programmer.

Why would you suspend a function?
- To avoid blocking the calling thread, i.e. it has to wait for something.

Notes:
- The caller and the callee play a game of ping-pong they don't run in parallel.
- The coroutine and the caller don't have to run in different threads (they can though).
- A coroutine is also an object, with a state and an API.
- A coroutine might live longer then it's calling context. So don't use reference parameters!
- A coroutine can only be suspended from within the coroutine itself at certain points.

## Coroutine Interface
The return object of a coroutine provides it's API: resume, destroy, etc.
Two things are needed to deal with coroutines:
1. A promise object that is used to communicate with the coroutine. The related promise type is the main customization point.
It defines callback functions that are used to deal with the coroutine.
2. A coroutine handle of type `std::coroutine_handle<>`, created when the coroutine is called. It can also be used to manage the state and the end of the coroutine.

Promise object and coroutine handle will be part of the coroutine return object.

## promise_type
The compiler generates code that interacts with the promise object. So the functions defined in the promise type are
called by that compiler generated code.

What does the promise type have to provide?
Functions for:
- initialization
- suspension `initial_suspend()`, `final_suspend()`, `yield_value()`
- resumption
- exception handling `unhandled_exception()`
- returning a value `get_return_object()`