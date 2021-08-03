#include <iostream>
#include <string.h>

template<typename T, int size>
class Stack {
  T m_Buffer[size];
  int m_Top{-1};
 public:
  void Push(const T&  element) {
    m_Buffer[++m_Top] = element;
  }
  const T& Top() const {
    return m_Buffer[m_Top];
  }
  void Pop();
  bool IsEmpty() {
    return m_Top == -1;
  }
  // shorthand notation: here "Stack" is sufficiant, although it is really Stack<T, size>
  static Stack Create() {
    return Stack<T, size>();
  }
};
// implement outside of declaration, "Stack" alone is not sufficient
template<typename T, int size>
void Stack<T, size>::Pop() {
  --m_Top;
}

//-------------------------------------------------------------------------------
int main() {
  // Stack<int, 512> s = Stack<int, 123>::Create(); 512 != 123, size is part of the type!
  Stack<int, 512> s = Stack<int, 512>::Create();
  s.Push(1);
  s.Push(2);
  s.Push(3);
  s.Push(4);
  s.Push(5);

  while (!s.IsEmpty()) {
    std::cout << s.Top() << " ";
    s.Pop();
  }

  return 0;
}
