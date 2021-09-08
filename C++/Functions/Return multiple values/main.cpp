#include <iostream>
#include <string>

#include <tuple>
#include <regex>
//-----------------------------------------------------------------------------
std::tuple<std::string, std::string> SplitAddress(std::string address) {
  std::regex address_RE(R"((\/\/.*)\/(.*))");
  std::smatch matches;

  if (std::regex_match(address, matches, address_RE)) {
    return {matches[1], matches[2]};
  } else {
    std::cout << "Address not valid\n";
    return {"", ""};
  }
}
//-------------------------------------------------------------------------------
std::tuple<int, std::string> GetCLIArguments() {
  int exit_code = -1;

  auto [val1, val2] = SplitAddress("//52.157.151.140:5671/wps_default");

  return {exit_code, val1};
}
//-------------------------------------------------------------------------------
int main() {
  auto [exit_code, url] = GetCLIArguments();

  std::cout << "Return value 1: " << exit_code << "\n";
  std::cout << "Return value 2: " << url << "\n";

  return 0;
}
