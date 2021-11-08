#ifndef STRING_UTILITIES_H_
#define STRING_UTILITIES_H_

#include <string>
#include <vector>
#include <algorithm>

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
  std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::toupper(c); });
  return str;
}

#endif  // STRING_UTILITIES_H_
