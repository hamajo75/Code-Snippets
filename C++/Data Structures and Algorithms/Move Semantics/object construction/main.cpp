#include <iostream>
#include <string.h>

#include <vector>
#include <chrono>  // NOLINT

// override new so we can see memory allocations
void* operator new(std::size_t count) {
    std::cout << "new: " << count << " bytes" << std::endl;
    return malloc(count);
}

class MyClass {
 public:
  int *Data;
  uint32_t Size;

  explicit MyClass(uint32_t size) {                                     // ctor
    std::cout << "MyClass ctor\n";
    Size = size;
    Data = new int[Size];
  }

  MyClass(const MyClass &other) {                                       // copy ctor
    Size = other.Size;
    Data = new int[Size];
    memcpy(Data, other.Data, other.Size);

    std::cout << "MyClass copy ctor\n";
  }

  MyClass(MyClass &&other) {                                            // move ctor
    Size = other.Size;
    Data = other.Data;

    other.Size = 0;  // !! very important, otherwise other's Destructor could
                     // kill our Data !!
    other.Data = nullptr;

    std::cout << "MyClass move ctor\n";
  }

  ~MyClass() { std::cout << "MyClass object destroyed\n"; }
};

class MyOtherClass {
 private:
  MyClass Data;

 public:
  explicit MyOtherClass(const MyClass &data) : Data(data) {  std::cout << "MyOtherClass ctor - reference\n"; }
  explicit MyOtherClass(MyClass &&data) : Data(std::move(data)) {
    std::cout << "MyOtherClass ctor - rvalue reference\n";
  }

  ~MyOtherClass() { std::cout << "MyOtherClass object destroyed\n"; }
};

class Device {
 public:
  std::string hardware_id;             // e.g. "00:11:22:33:FF:EE"
  std::string external_device_id;      // e.g. "3fb1840a-37e1-48db-81c0-cefcef716cab"
  std::string owner;                   // e.g. "master.gasDaemon", "slave.cameraDaemon"
  std::string device_type;             // e.g. "X-AM-8000", "CAMERA"
  std::string device_name;             // e.g. "Camera Left"

  Device() {
    std::cout << "Device ctor\n";

    this->hardware_id = "00:11:22:33:44:01";
    this->external_device_id = "3fb1840a-37e1-48db-81c0-cefcef716cab";
    this->owner = "master.gasDaemon";
    this->device_type = "X-AM-8000";
    this->device_name = "Gas Detectore upper left";
  }

  Device& operator=(const Device& other) {
  std::cout << "Device copy operator=\n";

  if (this == &other) return *this;

  this->hardware_id = other.hardware_id;
  this->external_device_id = other.external_device_id;
  this->owner = other.owner;
  this->device_type = other.device_type;
  this->device_name = other.device_name;
  return *this;
}
  Device(const Device& other) {
    std::cout << "Device copy ctor\n";
    *this = other;
  }

  Device& operator=(Device&& other) {
    std::cout << "Device move operator=\n";

    if (this == &other) return *this;

    this->hardware_id = std::move(other.hardware_id);
    this->external_device_id = std::move(other.external_device_id);
    this->owner = std::move(other.owner);
    this->device_type = std::move(other.device_type);
    this->device_name = std::move(other.device_name);
    return *this;
  }

  Device(Device&& other) {
    std::cout << "Device move ctor\n";
    *this = std::move(other);
  }
};

class Camera : public Device {
 public:
  std::string camera_light_status;
  std::string camera_status;
  std::string firmware_version;
  std::string serial_number;
  std::string video_resolution;

  Camera() = default;
  explicit Camera(const Device& device) : Device(device) {
    std::cout << "Camera copy ctor\n";
  }
  explicit Camera(Device&& device) : Device(std::move(device)) {
    std::cout << "Camera move ctor\n";
  }
};

void AddDevice(Device device) {
  std::vector<Camera> vec;
  Camera camera{std::move(device)};

  vec.push_back(std::move(camera));
}

//-------------------------------------------------------------------------------
int main(int argc, const char *argv[]) {
  // MyOtherClass o(MyClass{1000});          // invokes move ctor - cheap
  //                                         //   MyClass{1000} is an rvalue (anonymous temporary object)

  // MyClass o2{1000};
  // MyOtherClass oo2(o2);                   // invokes copy ctor - expensive
  // MyOtherClass oo2(std::move(o2));     // invokes move ctor - cheap


  auto start = std::chrono::high_resolution_clock::now();

  // for (int i = 0; i < 10000; ++i) {
    AddDevice(Device{});
  // }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> diff = end - start;
  std::cout << "time: " << diff.count();

  return 0;
}
