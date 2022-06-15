#include <iostream>
#include <string>
#include <array>

#include <cerrno>

std::pair<int, std::string> Execute(const std::string &cmd) {
  std::array<char,128> buffer;
  std::string output = "";
  FILE *pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    throw std::runtime_error("popen() failed!");
  try {
    while (fgets(buffer.data(), sizeof buffer, pipe) != NULL)
      output += buffer.data();
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);

  return std::make_pair(errno, output);
}

void GetMacAddressOfNetworkInterface(const std::string &net_if) {
  std::string cmd = "ifconfig " + net_if +
                    " | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}' ";
  std::system(cmd.c_str());
}

void CalculateMD5Hash(const std::string& input) {
  std::string cmd = "printf '%s' " + input + "| md5sum";
  std::system(cmd.c_str());
}

//-------------------------------------------------------------------------------
int main() {
  GetMacAddressOfNetworkInterface("wlp0s20f3");
  CalculateMD5Hash("Hello");

  auto result = Execute("systemctl get-default");
  std::cout << "error_nr: " << result.first << "\n" << result.second << "\n";

  return 0;
}
