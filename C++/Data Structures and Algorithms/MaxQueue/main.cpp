#include <cstddef>
#include <iostream>
#include <string>
#include <deque>

template<typename T>
class MaxQueue : public std::deque<T> {
 public:
  explicit MaxQueue(size_t size) : size_{size} {}

  void push(T element) {
    this->push_back(element);

    if (this->size() > size_)
      this->pop_front();
  }

 private:
  size_t size_;
};

template<typename T>
void PrintQueue(MaxQueue<T> q) {
  std::cout << "Queue elements: \n";
  for (auto element : q) {
    std::cout << element << "\n";
  }
}

//-------------------------------------------------------------------------------
int main() {
  MaxQueue<int> q{2};

  q.push(1);
  q.push(2);
  q.push(3);

  PrintQueue(q);

  q.push(4);
  q.push(5);

  PrintQueue(q);

  return 0;
}
