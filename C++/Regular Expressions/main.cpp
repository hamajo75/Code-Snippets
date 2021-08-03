#include <stdio.h>
#include <iostream>
#include <string.h>

#include <regex>
#include <fstream>

//-------------------------------------------------------------------------------
void ParsePostalCode() {
  // 2 letters\w{2}, some space (\s*), 5 digits (\d{5}), optionally followd by a dash and 4 digits (-\d{4})
  std::regex postal_code_RE(R"(\w{2}\s*\d{5}(-\d{4})?)");  // US postal code pattern: XXddddd-dddd and variants

  // R"( ... )" raw string literal: use backslashes and quotes directly

  std::string s("AA  12345-1234");

  // ---------------- regex_match() -----------------------------------------
  std::smatch matches;  // matched strings go here

  if (std::regex_match(s, matches, postal_code_RE))
    std::cout << "string object matched\n";

  std::cout << "found " << matches.size() << " matches: \n";
  unsigned int i = 0;
  for (auto m : matches)
    std::cout << "Match " << ++i << ": " << m << std::endl;

  // ---------------- regex_search() ----------------------------------------
  std::regex object_files_RE(R"(\w+\.o)");
  std::ifstream in("file.txt");
  if (!in)
    std::cerr << "File not found" << std::endl;

  i = 0;
  for (std::string line; getline(in, line);) {
    std::smatch matches;
    if (regex_search(line, matches, object_files_RE))
      std::cout << line << std::endl;
  }

  // ---------------- regex_replace() ---------------------------------------

  std::cout << "\n";
}
//-------------------------------------------------------------------------------
void ParseAddress() {
  std::regex address_RE(R"((?:\/\/)?([0-9.:a-z]*)\/(.*\/?.*))");
  std::smatch matches;  // matched strings go here

  std::string address {"0.0.0.0:5671/wps_default"};

  if (std::regex_match(address, matches, address_RE)) {
    std::cout << "address matched\n";
    std::cout << matches[1] << "\n";
    std::cout << matches[2] << "\n";
  } else {
    std::cout << "Not matched\n";
  }
}
//-------------------------------------------------------------------------------
int main() {
  // ParsePostalCode();
  ParseAddress();

  return 0;
}
