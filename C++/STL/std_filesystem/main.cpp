#include <iostream>
#include <streambuf>
#include <string>
#include <filesystem>

void CreateDirectory() {
  auto dir = "subdir";
  bool success = std::filesystem::remove(dir);
  std::cout << std::boolalpha << "dir deleted: " << success << "\n";
  if (!std::filesystem::exists(dir)) {
    success = std::filesystem::create_directory(dir);
    std::cout << std::boolalpha << "dir created: " << success << "\n";

    success = std::filesystem::create_directory(dir);
    std::cout << std::boolalpha << "dir created: " << success << "\n";
  }
}

//-------------------------------------------------------------------------------
int main() {
  CreateDirectory();
  return 0;
}
