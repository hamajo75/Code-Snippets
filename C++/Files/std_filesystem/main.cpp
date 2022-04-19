#include <ios>
#include <iostream>
#include <string.h>

#include <filesystem>

void Files() {
  std::filesystem::path file_path{"file.txt"};
  file_path.is_relative();
  std::cout << file_path.root_path() << "\n";
  std::cout << file_path.extension() << "\n";
  std::cout << file_path.filename() << "\n";
  std::cout << "file exists: " << std::boolalpha << std::filesystem::exists(file_path) << "\n";


  auto path = std::filesystem::path{file};
  auto new_path = path;
  new_path.replace_filename("bak_" + path.filename().string());
  std::filesystem::copy_file(path, new_path);
}

void Directories() {
  std::filesystem::create_directory("test");
  std::filesystem::create_symlink("target", "link");
}

//-------------------------------------------------------------------------------
int main() {
  // Directories();
  Files();

  return 0;
}
