#include <iostream>
#include <string>

struct SensorChannelA {
  int channel_number;
  std::string gas_type;
  std::string gas_unit;
  std::string gas_value;
};

struct SensorChannelB {
  int channel_number;
  std::string gas_type;
  std::string gas_unit;
  std::string gas_value;

  void operator=(const SensorChannelA& other) {
    this->channel_number = other.channel_number;
    this->gas_type = other.gas_type;
    this->gas_unit = other.gas_unit;
    this->channel_number = other.channel_number;
  }
};

SensorChannelB& SensorChannelA::operator=() {
  SensorChannelB b;
  b.channel_number = this->channel_number;
  b.gas_type = this->gas_type;
  b.gas_unit = this->gas_unit;
  b.channel_number = this->channel_number;

  return b;
}
//-------------------------------------------------------------------------------
int main() {
  SensorChannelA a = {0, "typeA", "", ""};
  SensorChannelB b;
  b = a;

  std::cout << "b.gas_type " << b.gas_type << "\n";

  return 0;
}
