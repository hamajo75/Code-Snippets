#include <iostream>
#include <future>

// Function that simulates an asynchronous operation
int fetchData()
{
    // Simulating some time-consuming task
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 42;
}

int main()
{
    // Creating a promise and its associated future
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    // Starting the asynchronous operation
    std::thread asyncOperation([&promise]() {
        int result = fetchData();
        promise.set_value(result);
    });

    // Continue with other tasks while waiting for the result
    std::cout << "Performing other tasks..." << std::endl;

    // Wait for the future to become ready and retrieve the result
    int result = future.get();

    // Display the result
    std::cout << "The result is: " << result << std::endl;

    // Clean up
    asyncOperation.join();

    return 0;
}
