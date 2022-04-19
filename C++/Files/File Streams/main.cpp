#include <iostream>
#include <string.h>

#include <sstream>
#include <fstream>

//-------------------------------------------------------------------------------
std::string readFileIntoString(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}
//-------------------------------------------------------------------------------
std::string readFile(const std::string& file_path) {
  std::ifstream file_ifs {file_path};
  std::string str;
  if (file_ifs) {
    std::ostringstream ss;
    ss << file_ifs.rdbuf();
    str = ss.str();
  }
  return str;
}
//-------------------------------------------------------------------------------
void writeFile(const std::string& file_path) {
  std::ofstream file_ofs(file_path);
  file_ofs << "file content\n";
  file_ofs << "file content\n";
  file_ofs << "file content\n";
  file_ofs.flush();
}
//-------------------------------------------------------------------------------
int main() {
  writeFile("file.txt");
  auto file_content = readFile("file.txt");
  std::cout << file_content;

  return 0;
}
