#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

/*std::lock_guard
- Ensures that the mutex is locked when entering a scope unlocked when leaving the scope.
- While the mutex is locked, no other thread can lock it.
*/

class ThreadSafeCounter {
private:
    mutable std::mutex mutex_;
    int value_ = 0;

public:
    void increment(int by = 1) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ += by;
    }

    // Getter
    int getValue() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return value_;
    }

    // Setter
    void setValue(int newValue) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ = newValue;
    }
};

void workerFunction(ThreadSafeCounter& counter) {
    for (int i = 0; i < 1000; ++i) {
        counter.increment();
    }
}

int main() {
    ThreadSafeCounter counter;

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(workerFunction, std::ref(counter));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value: " << counter.getValue() << std::endl;

    // Using the setter
    counter.setValue(42);
    std::cout << "New counter value: " << counter.getValue() << std::endl;

    return 0;
}
