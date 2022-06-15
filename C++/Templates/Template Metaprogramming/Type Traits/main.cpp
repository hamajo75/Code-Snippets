#include <iostream>
#include <string>

#include <type_traits>

/* Type Traits
Inspect and transform properties of types at compile time.

Is it a function, a class, an integer?
Conditional compilation

Used in template meta programming and conditional compilation.
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

class Class {};

void Simple() {
  std::cout << std::is_floating_point<Class>::value << '\n';
  std::cout << std::is_floating_point<float>::value << '\n';
  std::cout << std::is_floating_point<int>::value << '\n';
}

// conditional compilation
void algorithm_signed(int i) { /*...*/
}
void algorithm_unsigned(unsigned u) { /*...*/
}

template <typename T> void algorithm(T t) {
  if constexpr (std::is_signed<T>::value)             // conditional compilation
    algorithm_signed(t);
  else if constexpr (std::is_unsigned<T>::value)
    algorithm_unsigned(t);
  else
    static_assert(std::is_signed<T>::value || std::is_unsigned<T>::value,
                  "Must be signed or unsigned!");
}
//-------------------------------------------------------------------------------
int main() {
  Simple();

  return 0;
}
