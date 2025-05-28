#include <iostream>
#include <expected>
#include <vector>
#include <string>

std::expected<int, std::string> getInt(std::string arg) {
    try {
        return std::stoi(arg);
    }
    catch (...) {
        return std::unexpected{std::string(arg + ": Error")};
    }
}


int main() {

    std::cout << '\n';

    std::vector<std::string> strings = {"66", "foo", "-5"};

    for (auto s: strings) {                                 // (1)
        auto res = getInt(s);
        if (res) {
            std::cout << res.value() << ' ';                // (3)
        }
        else {
            std::cout << res.error() << ' ';                // (4)
        }
    }

    std::cout << '\n';

    for (auto s: strings) {                                 // (2)
        auto res = getInt(s);
        std::cout << res.value_or(2023) << ' ';             // (5)
    }

    std::cout << '\n';

}