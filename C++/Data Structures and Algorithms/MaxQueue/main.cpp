#include <cstddef>
#include <iostream>
#include <string>
#include <deque>

template<typename T>
class MaxQueue {
 public:
  explicit MaxQueue(size_t size) : size_{size} {}

  void Push(T element) {
    queue_.push_back(element);

    if (queue_.size() > size_)
      queue_.pop_front();
  }

  T Front() { return queue_.front(); }
  void Pop() { queue_.pop_front(); }
  size_t Empty() const { return queue_.empty(); }

  auto begin() { return queue_.begin(); }
  auto end() { return queue_.end(); }

 private:
  size_t size_;
  // use deque for iteration
  std::deque<T> queue_;
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

  q.Push(1);
  q.Push(2);
  q.Push(3);

  PrintQueue(q);

  q.Push(4);
  q.Push(5);

  PrintQueue(q);

  return 0;
}
