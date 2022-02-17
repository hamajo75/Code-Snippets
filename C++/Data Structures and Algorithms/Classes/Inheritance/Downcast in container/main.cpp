#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>

struct Device {
  std::string hardware_id;
};
struct Camera : public Device {
  std::string camera_light_status;
};
struct GasDetector : public Device {
  std::string gas_detector_status;
};

template<typename C>
Device* FindDevice(C& devices, std::function<bool(Device)> predicate) {
  auto it = std::find_if(devices.begin(), devices.end(), predicate);
  if (it == devices.end())
    return nullptr;
  return &*it;
}

using Cameras = std::vector<Camera*>;
using GasDetectors = std::vector<GasDetector*>;

struct DeviceManagement {
  Cameras cameras;
  GasDetectors gas_detectors;

  DeviceManagement() {
    cameras.push_back(new Camera{{""}, "camera_0"});
  }

  Device* Find(std::function<bool(Device)> predicate) const {
    auto device = FindDevice(cameras, predicate);
    if (device)
      return device;

    if ((device = FindDevice(gas_detectors, predicate)))
      return device;

    return device;
  }
};

//-------------------------------------------------------------------------------
int main() {
  DeviceManagement device_management;

  return 0;
}
