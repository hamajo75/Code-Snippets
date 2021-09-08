#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <boost/lexical_cast.hpp>
//-------------------------------------------------------------------------------
struct Journal {
  std::string title;
  std::vector<std::string> entries;

  explicit Journal(const std::string& title) : title(title) {}

  void add_entry(const std::string& entry) {
    static int count = 1;
    entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
  }

  // void save(const std::string& filename) {   // move this to a different class
  //   std::ofstream ofs(filename);             // if you change from file to db you only have to make the change there
  //   for (auto& e : entries)
  //     ofs << e << "\n";
  // }

};
//-------------------------------------------------------------------------------
// Separation of concerns
struct PersistenceManager {
  static void save(const Journal& j, const std::string& filename) {
    std::ofstream ofs(filename);
    for (auto& e : j.entries)
      ofs << e << "\n";
  }
};
//-------------------------------------------------------------------------------
int main() {
  Journal journal{"My Diary"};
  journal.add_entry("entry 1");
  journal.add_entry("entry 2");

  PersistenceManager::save(journal, "journal.txt");

  return 0;
}
