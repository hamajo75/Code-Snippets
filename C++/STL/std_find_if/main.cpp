#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<typename T>
class EntryFound {
 public:
  explicit EntryFound(const T& entry) : entry_{entry} {}

  bool operator() (const T& entry) const {
    return (entry.a == entry_.a) &&
           (entry.b == entry_.b);
  }
 private:
  T entry_;
};

struct Device {
  std::string a;
  std::string b;
};

int main() {
  std::vector<Device> vec = {{"a2", "b1"}, {"a2", "b2"}, {"a2", "b3"}};
  Device d = {"a2", "b1"};
  auto it = std::find_if(vec.begin(), vec.end(), EntryFound<Device>(d));

  if (it != vec.end())
    std::cout << "entry found: " << it->a << " " << it->b << "\n";
}