#include <string>
#include <array>

// Enum class that has a string representation for its values.

class MyEnum {
 public:
  enum values{kValue0 = 0, kValue1 = 1, kValue2 = 2};
  std::string ToString() const {
    return str_values_[value_];
  }

  bool SetFromString(const std::string& value) {
    for (unsigned int i = 0; i < str_values_.size(); ++i) {
      if (value == str_values_[i]) {
        value_ = i;
        return true;
      }
    }
    return false;
  }

  bool operator==(const MyEnum& other) const {
    return this->value_ == other.value_;
  }

  bool operator!=(const MyEnum& other) const {
    return !(*this == other);
  }

  bool operator==(const MyEnum::values& value) const {
    return this->value_ == value;
  }

  bool operator!=(const MyEnum::values& value) const {
    return !(this->value_ == value);
  }

  MyEnum& operator=(const MyEnum& other) {
    this->value_ = other.value_;
    return *this;
  }

  MyEnum& operator=(const MyEnum::values& value) {
    this->value_ = value;
    return *this;
  }

  MyEnum() = default;
  MyEnum(const MyEnum& other) {
    value_ = other.value_;
  }

  explicit MyEnum(const MyEnum::values value) {
    value_ = value;
  }

 private:
  inline static const std::array<std::string, 3> str_values_ = {"Value0", "Value1", "Value2"};
  int value_ = 0;
};