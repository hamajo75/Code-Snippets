#include <exception>
#include <stdio.h>
#include <string>
#include <cctype>
#include <algorithm>

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

#include "string_utilities.h"

/* functions: substring, replace, find, length
 */
//-------------------------------------------------------------------------------
void print(const std::string &name) {}         // std::string& is an lvalue-reference
void print2(const std::string &name) {}  // can also bind to rvalues
void print3(std::string &&name) {}       // rvalue-reference
//-------------------------------------------------------------------------------
void FindAndReplace() {
  std::string name = "Johann Hagler";

  // substr
  std::cout
      << name.substr(7, 12)
      << std::endl;  // substr(index, length) indexing starts at 0, 'Hagler'

  // replace
  std::cout << name.replace(0, 6, "Joe")
            << std::endl;  // replace(index, length)
  // find
  if (name.find("Hagler") != std::string::npos) {
      std::cout << "found!" << '\n';
  }
  std::string url = "127.0.0";
  std::cout << "url.substr(0, 9) " << url.substr(0, 9) << "\n";

  std::cout << "Replace(): " <<
    string_utilities::Replace("workplace_${workplaceId}.default", "${workplaceId}", "123") << "\n";

  using namespace std::literals;
  auto ip_address = ""s;
  auto pos = ip_address.find_last_of(".");
  auto length = ip_address.size();
  auto ip_address_plus_1 = ip_address.substr(0, pos + 1);

  try {
    ip_address_plus_1 += std::to_string(std::stoi(ip_address.substr(pos + 1, length - pos)) + 1);
  } catch(const std::exception& e) {
    std::cout << e.what() << "\n";
  }

  std::cout << "ip_address_plus_1: " << ip_address_plus_1 << "\n";
}
//-------------------------------------------------------------------------------
void StringManipulation() {
  std::string first = "Hello ";
  std::string second = "Joe";
  // print(first + second);   // compile error:
  // cannot bind non-const lvalue reference to an rvalue (first + second)
  print2(first + second);  // this works
  print3(first + second);  // now only this works

  std::string path = "my/path/to";
  if (path.back() != '/') path += '/';
  std::cout << "path: " << path << "\n";

  std::string value = "ch4";
  value = string_utilities::Uppercase(value);
  std::cout << "value.toupper(): " << value << "\n";
}

void FormatOutput() {
  std::cout << "[" << std::setw(3) << std::setfill('*') << "1]" << std::endl;
  std::cout << "2021-09-21T23:30:27." << std::setw(3) << std::setfill('0') << "999" << std::endl;
}

void SplitString() {
  // push line from CSV-file into vector, split at DELIMITER
  std::vector<std::string> str_array = string_utilities::SplitString("Dummy", ',');
  for (auto& s : str_array)
    std::cout << s << " ";
}

void StringConversion() {
  int i = 10;
  std::cout << "std::to_string " << std::to_string(i) << "\n";
}

inline void SortVectorOfStrings() {
  std::vector<std::string> v = { "12", "2", "10", "6", "4", "99", "12", "110" };

  std::cout << "before\n";
  for (auto e : v) {
    std::cout << e << "\n";
  }

  std::sort(v.begin(), v.end());

  std::cout << "after\n";
  for (auto e : v) {
    std::cout << e << "\n";
  }
}
#include <boost/algorithm/string.hpp>
void BoostFunctions() {
  std::string str = "\n alkdjflkadjfl     \n  hello \n next line   \n";

  boost::trim(str);
  std::cout << str << "\n";

  // boost::algorithm::replace_all(str, "\n", "");
}
//-------------------------------------------------------------------------------
int main() {
  FindAndReplace();
  // StringManipulation();
  // FormatOutput();
  // SplitString();
  // StringConversion();
  // SortVectorOfStrings();
  // BoostFunctions();

  return 0;
}
