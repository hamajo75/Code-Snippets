#include <linux/input-event-codes.h>
#include <linux/input.h>

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>


void ReadFromKeyboard() {
  std::filesystem::path event_file = "/dev/input/event2";
  std::ifstream file{event_file};
  file.exceptions(std::ios_base::badbit | std::ios_base::failbit);  // otherwise file.read is not blocking
  input_event event;

  while (true) {
    file.read((char*)&event, sizeof(event));
    std::cout << "event.code: " << event.code << "\n";
    std::cout << "event.type: " << event.type << "\n";
    std::cout << "event.value: " << event.value << "\n";
    std::cout << "event.tv_sec: " << event.time.tv_sec << "\n";
    std::cout << "event.tv_usec: " << event.time.tv_usec << "\n";
  }
}

//-------------------------------------------------------------------------------
int main() {

  ReadFromKeyboard();
  return 0;
}
