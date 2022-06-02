#include <iostream>
#include <string>

/* Notes:
C++ doesn't have multiple dispatch (only single dispatch)
Problem: we have multiple functions with the same name, how to select,
         which one will be called.

         Multiple dispatch: select the function matching the multiple runtime types
           in the function call.
         Single dispatch (runtime polymorphism): There is an object with a
           member function. Selecting the function is done based on a single
           special parameter (this), i.e. the runtime type of "this".

Good article: https://www.fluentcpp.com/2020/05/22/how-to-assign-derived-classes-in-cpp/
*/

// // Easy solution:
// struct Device {
//   std::string type_ = "Device";

//   explicit Device(std::string type) : type_{type} {}
//   virtual Device& operator=(Device const& other) = 0;
//   virtual ~Device() = 0;
// };

// Device& Device::operator=(Device const& other) = default;
// Device::~Device() = default;

// struct Camera : public Device {
//   int value_;
//   explicit Camera(int value) : Device{"Camera"}, value_{value} {}
//   Camera& operator=(Camera const& other) = default;
//   Camera& operator=(Device const& other) override {
//     if (auto* other_concrete = dynamic_cast<Camera const*>(&other)) {    // straightforward but duplicate code
//       *this = *other_concrete;
//     }
//     return *this;
//   }
// };

// struct GasDetector : public Device {
//   int value_;
//   explicit GasDetector(int value) : Device{"GasDetector"}, value_{value} {}
//   GasDetector& operator=(GasDetector const& other) = default;
//   GasDetector& operator=(Device const& other) override {
//     if (auto* other_concrete = dynamic_cast<GasDetector const*>(&other)) {
//       *this = *other_concrete;
//     }
//     return *this;
//   }
// };

// CRTP solution
template <typename Derived, typename Base> struct VirtualAssignable : Base {
  explicit VirtualAssignable(std::string type) : Base{type} {}
  VirtualAssignable &operator=(Base const &other) override {
    auto &thisDerived = static_cast<Derived &>(*this);
    if (auto *otherDerived = dynamic_cast<Derived const *>(&other)) {
      thisDerived = *otherDerived;
    } else {
      std::cout << "Wrong type for assignment\n";
    }
    return thisDerived;
  }
};

struct Device {
  std::string type_ = "Device";

  explicit Device(std::string type) : type_{type} {}
  virtual Device& operator=(Device const& other) = 0;
  virtual ~Device() = 0;
};

Device& Device::operator=(Device const& other) = default;
Device::~Device() = default;

struct Camera : public VirtualAssignable<Camera, Device> {
  int value_;
  explicit Camera(int value) : VirtualAssignable{"Camera"}, value_{value} {}
};

struct GasDetector : public VirtualAssignable<GasDetector, Device> {
  int value_;
  explicit GasDetector(int value) : VirtualAssignable{"GasDetector"}, value_{value} {}
};

//-------------------------------------------------------------------------------
int main() {
  Camera c1{1};
  Camera c2{2};

  Device& b1 = c1;
  Device& b2 = c2;

  b2 = b1;

  std::cout << "b2.type_ " << b2.type_ << "\n";
  std::cout << "c2.value_ " << c2.value_ << "\n";

  GasDetector g1{1};
  b2 = g1;
  b2 = b1;

  return 0;
}
