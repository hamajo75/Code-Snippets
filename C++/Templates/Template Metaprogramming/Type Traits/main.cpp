#include <iostream>
#include <string>

#include <type_traits>
#include <typeinfo>

template<typename T1, typename T2>
typename std::conditional <(sizeof(T1) < sizeof(T2)), T1, T2>::type gcd(T1 a, T2 b){
  static_assert(std::is_integral<T1>::value, "T1 should be an integral type!");
  static_assert(std::is_integral<T2>::value, "T2 should be an integral type!");
  if( b == 0 ){ return a; }
  else{
    return gcd(b, a % b);
  }
}

void UseTemplate() {
  std::cout << "gcd(100,10)= " <<  gcd(100,10)  << std::endl;
  std::cout << "gcd(100,33)= " << gcd(100,33) << std::endl;
  std::cout << "gcd(100,0)= " << gcd(100,0)  << std::endl;

  std::cout << std::endl;

  std::cout << "gcd(100,10LL)= " << gcd(100,10LL) << std::endl;

  std::conditional <(sizeof(100) < sizeof(10LL)), long long, long>::type uglyRes = gcd(100,10LL);
  auto res= gcd(100,10LL);
  auto res2= gcd(100LL,10L);

  std::cout << "typeid(gcd(100,10LL)).name(): " << typeid(res).name() << std::endl;
  std::cout << "typeid(gcd(100LL,10L)).name(): " << typeid(res2).name() << std::endl;
}

void Simple() {
  std::cout << std::endl;
  std::cout << std::boolalpha;  // print true / false instead of 1 / 0

  std::cout << "is_void<void>::value: " << std::is_void<void>::value << std::endl;
  std::cout << "std::is_integral<short>::value: " << std::is_integral<short>::value << std::endl;
  std::cout << "std::is_floating_point<double>::value: " << std::is_floating_point<double>::value << std::endl;
  std::cout << "std::is_array<int []>::value: " << std::is_array<int [] >::value << std::endl;
  std::cout << "std::is_pointer<int*>::value: " << std::is_pointer<int*>::value << std::endl;
  std::cout << "std::is_null_pointer<std::nullptr_t>::value: " << std::is_null_pointer<std::nullptr_t>::value << std::endl;
  struct A{
    int a;
    int f(double){return 2011;}
  };
  std::cout << "std::is_member_object_pointer<int A::*>::value: " << std::is_member_object_pointer<int A::*>::value << std::endl;
  std::cout << "std::is_member_function_pointer<int (A::*)(double)>::value: " << std::is_member_function_pointer<int (A::*)(double)>::value << std::endl;
  enum E{
    e = 1,
  };
  std::cout << "std::is_enum<E>::value: " << std::is_enum<E>::value << std::endl;
  union U{
    int u;
  };
  std::cout << "std::is_union<U>::value: " << std::is_union<U>::value << std::endl;
  std::cout << "std::is_class<string>::value: " << std::is_class<std::string>::value << std::endl;
  std::cout << "std::is_function<int * (double)>::value: " << std::is_function<int * (double)>::value << std::endl;
  std::cout << "std::is_lvalue_reference<int&>::value: " << std::is_lvalue_reference<int&>::value << std::endl;
  std::cout << "std::is_rvalue_reference<int&&>::value: " << std::is_rvalue_reference<int&&>::value << std::endl;

  std::cout << std::endl;
}

// conditional compilation
void algorithm_signed  (int i)      { /*...*/ }
void algorithm_unsigned(unsigned u) { /*...*/ }

template <typename T>
void algorithm(T t) {
  if constexpr(std::is_signed<T>::value)
    algorithm_signed(t);
  else
    if constexpr (std::is_unsigned<T>::value)
        algorithm_unsigned(t);
    else
        static_assert(std::is_signed<T>::value || std::is_unsigned<T>::value, "Must be signed or unsigned!");
}
//-------------------------------------------------------------------------------
int main() {
  // Simple();
  UseTemplate();

  return 0;
}

/* Type Traits
Inspect and transform properties of types at compile time.

Is it a function, a class, an integer?
Conditional compilation

*/
// primary type categories
template <class T> struct is_void;
template <class T> struct is_integral;
template <class T> struct is_floating_point;
template <class T> struct is_array;
template <class T> struct is_pointer;
template <class T> struct is_reference;
template <class T> struct is_member_object_pointer;
template <class T> struct is_member_function_pointer;
template <class T> struct is_enum;
template <class T> struct is_union;
template <class T> struct is_class;
template <class T> struct is_function;
template <class T> struct is_lvalue_reference;
template <class T> struct is_rvalue_reference;
