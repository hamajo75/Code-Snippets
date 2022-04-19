#include <ios>
#include <iostream>
#include <string.h>

#include <filesystem>

void Files() {

  std::cout << "file exists: " << std::boolalpha << std::filesystem::exists("file.txt") << "\n";
}

void Directories() {
  std::filesystem::create_directory("test");
  std::filesystem::create_symlink("target", "link");
}

//-------------------------------------------------------------------------------
int main() {
  Directories();
  Files();

  return 0;
}
