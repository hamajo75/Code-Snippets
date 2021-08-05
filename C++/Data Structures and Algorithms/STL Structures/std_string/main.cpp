#include <stdio.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <vector>

/* functions: substring, replace, find, length
 */
//-------------------------------------------------------------------------------
std::vector<std::string> splitString(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void print(const std::string &name) {}         // std::string& is an lvalue-reference
void print2(const std::string &name) {}  // can also bind to rvalues
void print3(std::string &&name) {}       // rvalue-reference
//-------------------------------------------------------------------------------
int main(int argc, const char *argv[]) {
  std::string name = "Johann Hagler";

  std::cout
      << name.substr(7, 12)
      << std::endl;  // substr(index, length) indexing starts at 0, 'Hagler'
  std::cout << name.replace(0, 6, "Joe")
            << std::endl;  // replace(index, length)

  std::string first = "Hello ";
  std::string second = "Joe";
  // print(first + second);   // compile error:
  // cannot bind non-const lvalue reference to an rvalue (first + second)
  print2(first + second);  // this works
  print3(first + second);  // now only this works

  // push line from CSV-file into vector, split at DELIMITER
  const char DELIMITER = ';';
  std::vector<std::string> str_array = splitString("Dummy;String", DELIMITER);

  // string.find
  if (name.find("Hagler") != std::string::npos) {
      std::cout << "found!" << '\n';
  }

  return 0;
}
