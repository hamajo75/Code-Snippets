#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

// STL functions and datatypes used
/*
- std::thread
- std::thread::join
- std::this_thread::get_id
- std::this_thread::sleep_for
- std::chrono::milliseconds
- std::move
*/
//-----------------------------------------------------------------------------
void f1(int n) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Thread 1 executing" << std::this_thread::get_id() << "\n";
    ++n;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
//-----------------------------------------------------------------------------
void f2(int* n) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Thread 2 executing" << std::this_thread::get_id() << "\n";
    ++n;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
//-----------------------------------------------------------------------------
class foo {
 public:
  void bar() {
    for (int i = 0; i < 5; ++i) {
      std::cout << "Thread 3 executing" << std::this_thread::get_id() << "\n";
      ++n;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
  int n = 0;
};
//-----------------------------------------------------------------------------
class baz {
 public:
  void operator()() {
    for (int i = 0; i < 5; ++i) {
      std::cout << "Thread 4 executing" << std::this_thread::get_id() << "\n";
      ++n;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
  int n = 0;
};
void Basic() {
  int n = 0;
  foo f;
  baz b;
  std::thread t1;                   // t1 is not a thread
  std::thread t2(f1, n + 1);        // pass by value
  std::thread t3(f2, &n);           // pass by reference
  std::thread t4(
      std::move(t3));               // t4 is now running f2(). t3 is no longer a thread
  std::thread t5(&foo::bar, &f);    // t5 runs foo::bar() on object f
  std::thread t6(b);                // t6 runs baz::operator() on a copy of object b
  t2.join();
  t4.join();
  t5.join();
  t6.join();
  std::cout << "Final value of n is " << n << '\n';
  std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
  std::cout << "Final value of b.n (baz::n) is " << b.n << '\n';
}
void thread_fun() {
  std::cout << "having fun\n";
}
//-----------------------------------------------------------------------------
int main() {
  Basic();

  std::thread t(thread_fun);  // will cause: terminate called without an active exception


  return 0;
}