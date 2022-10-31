#include <iostream>
#include <string.h>
#include <tuple>

// template <typename... T> struct MessageBody {};

// template <typename T, typename... Rest> struct MessageBody<T, Rest...> {
//   MessageBody(const T &first, const Rest &...rest)
//       : first(first), rest(rest...) {}

//   T first;
//   MessageBody<Rest...> rest; // specialization-> we need to declare it like
//                              // this: MessageBody<T, Rest ...>
// };

// template <typename... T> struct Message {
//   Message(std::string header, const T &...args)
//       : MessageHeader{header}, MessageBody{args...} {}

//   MessageBody<T...> MessageBody;
//   std::string MessageHeader;
// };

// void UseTemplateStruct() {
//   Message<int, std::string> message{"header", 1, "data"};

//   std::cout << "message.MessageHeader " << message.MessageHeader << "\n";
//   std::cout << message.MessageBody.first << "\n";
//   std::cout << message.MessageBody.rest.first << "\n";
// }
//-------------------------------------------------------------------------------
// unpack parameters using fold expressions
template <typename... T>
auto sum(const T &...x) {
  return (x + ...); // fold expression
}
//-------------------------------------------------------------------------------
// if fold expression doesn't work, use recursion
template <typename T> auto sum2(const T &x) { return x; }

template <typename T1, typename... T> auto sum2(const T1 &x1, const T &...x) {
  return (x1 + sum2(x...));
}
//-------------------------------------------------------------------------------
// Args -> parameter pack
template <typename... Args> void printer(Args &&...args) {
  (std::cout << ... << args) << "\n";
}
//-------------------------------------------------------------------------------
// use initializer_list
// drawback: all arguments have to be of the same type
template <typename T> void print(std::initializer_list<T> args) {
  for (const auto &x : args) {
    std::cout << x << " ";
  }
}
//-------------------------------------------------------------------------------
// ...args   pack
// args...   unpack
void print2() {} // base case

template <typename T, typename... Params> void print2(T x, Params... args) {
  std::cout << "sizeof... " << sizeof...(args) << "\n";
  std::cout << x << " ";
  print2(args...);
}

void FunctionTemplates() {
  std::cout << sum(1, 2, 3, 4, 5) << "\n";
  std::cout << sum2(1, 2.4f, 4, 5) << "\n";

  printer("a", 1, 0.5f);
  print({1, 2, 3, 4, 5});
  print2("\n", 1, 2.3f, "a");
  std::cout << "\n";
}

// handling arguments param pack when
// arguments are of different types
// template< typename ... Args >
auto args_tuple = [](auto &&...args) {
  if constexpr (1 > (sizeof...(args))) {
    return std::make_tuple();
  }
  auto tup_list = std::make_tuple(args...);
  using arg_list_type = decltype(tup_list);

  return tup_list;
};

//-------------------------------------------------------------------------------
int main() {
  FunctionTemplates();
  // UseTemplateStruct();

  auto args = args_tuple(1, "ldafjk", true);

  return 0;
}
