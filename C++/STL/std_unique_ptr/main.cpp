#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <fstream>

std::string ExecuteCommand(const std::string &cmd) {
  std::array<char, 32> buffer;
  std::string result;

  // will automatically call pclose
  std::unique_ptr<FILE, decltype(&pclose)>
    pipe(popen(cmd.c_str(), "r"), pclose);

  if (!pipe) {
    auto error_msg = std::string("Failed to run process: \"") +
                     cmd;

    throw std::runtime_error(error_msg);
  }

  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  return result;
}

// helper function for the custom deleter demo below
void close_file(std::FILE* fp) {
    std::fclose(fp);
}

void UseCustomDeleter() {
  std::ofstream("demo.txt") << 'x';
  {
    using unique_file_t = std::unique_ptr<std::FILE, decltype(&close_file)>;
    unique_file_t fp(std::fopen("demo.txt", "r"), &close_file);
    if (fp)
        std::cout << char(std::fgetc(fp.get())) << '\n';
  }  // `close_file()` called here (if `fp` is not null)
}

//-------------------------------------------------------------------------------
int main() {
  auto output = ExecuteCommand("ls");
  UseCustomDeleter();

  return 0;
}
