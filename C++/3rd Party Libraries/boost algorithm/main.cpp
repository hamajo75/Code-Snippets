#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

std::vector<std::string> SplitString(const std::string &s, const std::string &delimiter) {
  std::vector<std::string> tokens;
  boost::split(tokens, s, boost::is_any_of(delimiter));
  return tokens;
}

// std::string Replace(const std::string &str, const std::string &this_str, const std::string &that_str) {
//   std::string return_str = str;
//   boost::algorithm::replace_all(return_str, this_str, that_str);
//   return return_str;
// }

//-------------------------------------------------------------------------------
int main() {
  std::string str = "param1,param2,param3";
  std::vector<std::string> str_vector = SplitString(str, ",");

  std::cout << "str_vector[0] "; //<< str_vector[0] << "\n";

  return 0;
}
