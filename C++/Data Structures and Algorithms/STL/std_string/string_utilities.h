#ifndef STRING_UTILITIES_H_
#define STRING_UTILITIES_H_

#include <algorithm>
#include <string>
#include <vector>

namespace string_utilities {

std::vector<std::string> SplitString(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string Uppercase(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return str;
}

std::string Replace(const std::string &str, const std::string &this_str, const std::string &that_str) {
  if (this_str.empty() || str.empty())
    return str;

  std::string out_str = str;
  size_t position = 0;
  while ((position = out_str.find(this_str, position)) != std::string::npos) {
    out_str.replace(position, this_str.length(), that_str);
    position += that_str.length();
  }
  return out_str;
}

}  // namespace string_utilities

#endif // STRING_UTILITIES_H_
