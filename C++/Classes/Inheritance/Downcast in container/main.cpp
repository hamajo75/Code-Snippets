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
static decltype(auto) FindDevice(C& devices, std::function<bool(Device)> predicate) {
  auto it = std::find_if(devices.begin(), devices.end(), predicate);
  // if (it == devices.end())
  //   return Device{};
  return &(*it);
}

using Cameras = std::vector<Camera>;
using GasDetectors = std::vector<GasDetector>;

struct DeviceManagement {
  Cameras cameras;
  GasDetectors gas_detectors;

  DeviceManagement() {
    Camera c;
    c.hardware_id = "123";
    c.camera_light_status = "123_camera_light_status";
    cameras.push_back(c);
  }

  // ------------------- const_cast solution ---------------------------------------------
  // const Device& Find(const std::string& hardware_id) const {
  //   return FindDevice(cameras, [&hardware_id](const auto& device){
  //     return device.hardware_id == hardware_id;
  //   });
  // }

  // Device& Find(const std::string& hardware_id) {
  //   return const_cast<Device&>(
  //     static_cast<const DeviceManagement*>(this)->Find(hardware_id));   // add const first! this is the Scott Meyer trick
  // }

  // ------------------- C++ 14 solution ---------------------------------------------
  template<typename Self>
  static decltype(auto) FindCommon(Self* self, const std::string& hardware_id) {
    return FindDevice(self->cameras, [&hardware_id](const auto& device){
      return device.hardware_id == hardware_id;
    });
  }

  Device* Find(const std::string& hardware_id) {
    return FindCommon(this, hardware_id);
  }

  const Device* Find(const std::string& hardware_id) const {
    return FindCommon(this, hardware_id);
  }
  // --------------------------------------------------------------------------------

  std::string GetStatus(const std::string& hardware_id) const {
    return reinterpret_cast<const Camera*>(Find(hardware_id))->camera_light_status;
  }
};

//-------------------------------------------------------------------------------
int main() {
  DeviceManagement device_management;

  device_management.Find("123")->hardware_id = "456";
  std::cout << "device_management.cameras[0].hardware_id: " << device_management.cameras[0].hardware_id << "\n";

  std::cout << "device_management.GetStatus: " << device_management.GetStatus("456") << "\n";

  return 0;
}
