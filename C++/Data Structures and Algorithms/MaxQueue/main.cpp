#include <cstddef>
#include <ios>
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
  bool Empty() const { return queue_.empty(); }

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

void test_MaxQueue() {
  MaxQueue<int> q{2};

  std::cout << std::boolalpha << "q.Empty(): " << q.Empty() << "\n";
  q.Push(1);
  q.Push(2);
  q.Push(3);

  PrintQueue(q);

  q.Push(4);
  q.Push(5);

  std::cout << std::boolalpha << "q.Empty(): " << q.Empty() << "\n";
  std::cout << "q.Front(): " << q.Front() << "\n";
  PrintQueue(q);
  q.Pop();

  PrintQueue(q);
}

//-------------------------------------------------------------------------------
int main() {

  test_MaxQueue();
  return 0;
}
