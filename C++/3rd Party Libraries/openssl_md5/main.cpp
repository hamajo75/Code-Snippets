#include <string>
#include <iostream>
#include <openssl/md5.h>

// Print the MD5 sum as hex-digits.
void print_md5_sum(unsigned char *md) {
  int i;
  for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
    printf("%02x", md[i]);
  }
}

std::string GenerateMD5Hash(const std::string& input) {
  unsigned char md5_value[MD5_DIGEST_LENGTH];
  MD5((unsigned char *)input.data(), input.size(), md5_value);

  char res[2*MD5_DIGEST_LENGTH];
  int i;
  for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
    std::sprintf(res + 2 * i, "%02x", md5_value[i]);  // NOLINT
  }

  return std::string{res};
}

int main(int argc, char *argv[]) {
  std::string input = R"_({"workplaceState":"STANDBY","sequenceNumber":12})_";
  // std::string input = R"_(Hello)_";
  std::cout << GenerateMD5Hash(input) << "\n";

  return 0;
}