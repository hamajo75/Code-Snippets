#include <iostream>
#include <string>

#include <vector>
#include <algorithm>

struct Device {
  std::string id;
};

using Devices = std::vector<Device>;
//-------------------------------------------------------------------------------
int main() {
  Devices devices = {{"1"}, {"2"}, {"1"}};

  std::sort(devices.begin(), devices.end(),
    [](const Device& d1, const Device& d2){
      return d1.id == d2.id;
    }
  );

  devices.erase(std::unique(devices.begin(), devices.end(),
    [](const Device& d1, const Device& d2){
      return d1.id == d2.id;
    }
    ), devices.end());

  for (const auto& device : devices)
    std::cout << device.id << "\n";

  return 0;
}
