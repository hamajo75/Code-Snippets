#include <iostream>
#include <string>

#include <utility>
#include <array>

struct ExecutionResult {
  int error;
  std::string output;
};

ExecutionResult Execute(const std::string &cmd) {
  std::array<char, 128> buffer;
  std::string output = "";
  std::string cmd_redirected;
  cmd_redirected = cmd + " 2>&1";   // redirect stderr to stdout

std::cout << cmd_redirected << "\n";

  FILE *pipe = popen(cmd_redirected.c_str(), "r");

  // C++ 11 alternative with custom deleter
  // std::unique_ptr<FILE, decltype(&pclose)>
  //   pipe(popen(cmd.c_str(), "r"), pclose);

  ExecutionResult error_result{-1, "Failed to execute command"};
  if (!pipe)
    return error_result;
  try {
    while (fgets(buffer.data(), sizeof buffer, pipe) != NULL)
      output += buffer.data();
  } catch (...) {
    pclose(pipe);
    return error_result;
  }

  auto error_code = pclose(pipe);
  return {error_code, output};
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
  // GetMacAddressOfNetworkInterface("enp0s3");
  // CalculateMD5Hash("Hello");

  auto result = Execute("ifconfig eth0");
  std::cout << "error_nr: " << result.error << "\n" << result.output << "\n";
  result = Execute("grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}' <<< absd");

  return 0;
}
