#include <iostream>

template<typename T>
class PrettyPrinter {
  T *m_pData;
 public:
  PrettyPrinter(T* data) : m_pData{data} {

  }
  void Print() {
    std::cout << "{" << *m_pData << "}" << "\n";
  }
};
//-----------------------------------------------------------------------------
// specialize the above class for char*
template<>
class PrettyPrinter<char*> {
  char *m_pDachara;
 public:
  PrettyPrinter(char* data) : m_pData{data} {

  }
  void Print() {
    std::cout << "{" << *m_pData << "}" << "\n";
  }
};
//-----------------------------------------------------------------------------
int main() {
  int data = 5;
  float f = 9.2f;

  PrettyPrinter<int> p1(&data);
  p1.Print();
  PrettyPrinter<float> p2(&f);
  p2.Print();

  char *p{"Hello World"};
  PrettyPrinter<char*> p3(&p);
  p3.Print();


}