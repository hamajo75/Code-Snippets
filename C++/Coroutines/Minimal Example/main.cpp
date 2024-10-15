#include <iostream>
#include <coroutine>

struct ReturnObject {
    // The compiler will generate code that calls the functions in the promise_type struct.
    struct promise_type {
        // This is what the caller of the coroutine will get as a return value.
        ReturnObject get_return_object() {
            return ReturnObject{
                std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() { return {}; }  // Don't suspend initially
        std::suspend_always final_suspend() noexcept { return {}; }  // Suspend at the end
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    ReturnObject(std::coroutine_handle<promise_type> h) : handle(h) {}

    ~ReturnObject() {
        if (handle) handle.destroy(); // Clean up coroutine resources
    }
};

ReturnObject my_coroutine() {
    std::cout << "Hello ";
    co_await std::suspend_always{};  // Suspend here
    std::cout << "Coroutine!\n";     // This will run when resumed
}

int main() {
    auto returnObj = my_coroutine();  // The coroutine starts and prints "Hello"

    std::cout << "World\n";           // Now "World" is printed

    returnObj.handle.resume();        // Resume the coroutine and print "Coroutine!"

    return 0;
}
