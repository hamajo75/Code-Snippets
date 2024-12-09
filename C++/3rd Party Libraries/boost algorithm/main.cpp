#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

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

std::string GenerateMD5Hash(const std::string& input) {
  boost::uuids::detail::md5 hash;
  boost::uuids::detail::md5::digest_type digest;

  hash.process_bytes(input.data(), input.size());
  hash.get_digest(digest);

  const auto intDigest = reinterpret_cast<const int*>(&digest);
  std::string result;
  boost::algorithm::hex(
    intDigest,
    intDigest + (sizeof(boost::uuids::detail::md5::digest_type)/sizeof(int)),
    std::back_inserter(result));
  return result;
}

//-------------------------------------------------------------------------------
int main() {
  std::string str = "param1,param2,param3";
  std::vector<std::string> str_vector = SplitString(str, ",");

  std::cout << "str_vector[0] "; //<< str_vector[0] << "\n";

  return 0;
}
