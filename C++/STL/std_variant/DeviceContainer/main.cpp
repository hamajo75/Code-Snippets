#include <iostream>
#include <string>
#include <vector>

#include <variant>

struct Device {
  std::string hardware_id;             // e.g. "00:11:22:33:FF:EE"
  std::string external_device_id;      // e.g. "3fb1840a-37e1-48db-81c0-cefcef716cab"
  std::string owner;                   // e.g. "master.gasDaemon", "slave.cameraDaemon"
  std::string device_type;             // e.g. "GAS_DETECTOR", "CAMERA"
  std::string device_name;             // e.g. "Camera Left"

  // virtual void FindDevice() {}      // with virtual functions the initializer list init doesn't work anymore
  // virtual ~Device() = default;
};

struct PairingDevice : public Device {
  std::string pairing_status;
  std::string paired_to_device_id;
};

struct Empty : public PairingDevice {};

struct Camera : public PairingDevice {
  std::string camera_light_status;
  std::string camera_status;
  std::string firmware_version;
  std::string serial_number;
  std::string video_resolution;
};

struct SensorChannel {
  int channel_number;
  std::string gas_type;
  std::string gas_unit;
  std::string gas_value;
};

struct GasDetector : public PairingDevice {
  std::string gas_detector_status;
  std::string gas_detector_type;
  std::vector<SensorChannel> sensor_channels;
};

struct Battery : public Device {
  std::string battery_location;
  std::string battery_status;
  std::string charging_status;
};

using Cameras = std::vector<Camera>;
using GasDetectors = std::vector<GasDetector>;
struct Intercom : public PairingDevice {
  Cameras cameras;
  GasDetectors gas_detectors;
  std::string operating_system_type;
  std::string operating_system_version;
  std::string serial_number;
  std::string software_version;
};

using WorkplaceDevice = std::variant<Empty, GasDetector, Camera, Intercom>;
using WorkplaceDevices = std::vector<WorkplaceDevice>;

void GetDeviceNames(const WorkplaceDevices& devices) {
  for (const auto& device : devices) {
    auto device_name = std::visit([](auto&& device){ return device.device_name; }, device);
    std::cout << "device.DeviceName: " << device_name << "\n";
  }
}

WorkplaceDevice GetDevice(const WorkplaceDevices& devices, const std::string& hardware_id) {
  for (const auto& device : devices) {
    auto device_hardware_id = std::visit([](auto&& device){ return device.hardware_id; }, device);
    if (device_hardware_id == hardware_id)
      return device;
  }
  return Empty{};
}

void AddDevice(WorkplaceDevices& devices, const WorkplaceDevice& device) {
  devices.push_back(std::move(device));
}

Cameras GetCameras(const WorkplaceDevices& devices) {
  Cameras cameras;
  for (const auto& device : devices) {
    auto device_type = std::visit([](auto&& device){ return device.device_type; }, device);
    if (device_type == "CAMERA") {
      cameras.push_back(std::get<Camera>(device));
    }
  }
  return cameras;
}
//-------------------------------------------------------------------------------
int main() {
  WorkplaceDevices devices;

  Device device {"1", "", "", "CAMERA", "camera"};

  Camera camera {{device,  // Device
                    "", ""},                            // PairingDevice
                    "", "", "", "", ""};                // Camera
  GasDetector gas_detector {{{"2", "", "", "", "gas_detector"},
                               "", ""},
                               "", "", {}};
  Intercom intercom {{{"3", "", "", "", "intercom"}, "", ""},
                       {camera}, {gas_detector}, "", "", "", ""
                      };

  // Battery battery = {{"4", "", "", "", "camera"},    // Device
  //                     "", "", ""                     // Battery
  //                   };
  AddDevice(devices, camera);
  AddDevice(devices, Camera{{{"4", "", "", "CAMERA", "camera2"},  // Device
                    "", ""},                                      // PairingDevice
                    "", "", "", "", ""});                         // Camera);

  AddDevice(devices, gas_detector);
  AddDevice(devices, intercom);

  GetDeviceNames(devices);

  try {
    WorkplaceDevice device = GetDevice(devices, "1");
    Camera c = std::get<Camera>(device);
    std::cout << c.device_name << "\n";
  } catch (const std::bad_variant_access& e) {
    std::cout << e.what() << '\n';
  }

  for (const auto& camera : GetCameras(devices))
    std::cout << camera.device_name << "\n";

  return 0;
}
