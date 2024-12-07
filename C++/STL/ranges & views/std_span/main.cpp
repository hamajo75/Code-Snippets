#include <iostream>
#include <span>
#include <vector>

template<typename T>
void processNumbers(std::span<T> numbers) {
    for (T num : numbers) {
        std::cout << num << "\n";
    }
}

int main() {
    int arr[] = {10, 20, 30, 40};
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0, 5.0};

    processNumbers<int>(arr);  // Works with raw arrays
    processNumbers<double>(vec);  // Works with std::vector
}
