#include <iostream>
#include <string>

std::string exec(const char* cmd) {
  char buffer[128];
  std::string result = "";
  FILE* pipe = popen(cmd, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
      while (fgets(buffer, sizeof buffer, pipe) != NULL)
          result += buffer;
  } catch (...) {
      pclose(pipe);
      throw;
  }
  pclose(pipe);
  return result;
}

void GetMacAddressOfNetworkInterface(const std::string& net_if) {
  std::string cmd = "ifconfig " + net_if + " | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}' ";
  std::system(cmd.c_str());
}

//-------------------------------------------------------------------------------
int main() {
  GetMacAddressOfNetworkInterface("enp0s3");
  return 0;
}
