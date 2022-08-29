#include <iostream>
#include <string>
#include <optional>
#include <vector>

struct SensorChannelA {
  int channel_number;
  std::string gas_type;
  std::string gas_unit;
  std::string gas_value;
  void operator=(SensorChannelA& other);
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

void SensorChannelA::operator=(SensorChannelA& other) {
  other.channel_number = this->channel_number;
  other.gas_type = this->gas_type;
  other.gas_unit = this->gas_unit;
  other.gas_value = this->gas_value;
}

void SensorChannelExample() {
  SensorChannelA a = {0, "typeA", "", ""};
  SensorChannelB b;
  b = a;

  std::cout << "b.gas_type " << b.gas_type << "\n";
}

struct Alarm {
  std::optional<std::string> additional_information;
  std::string alarm_type;
  std::optional<std::string> device_id;
};

using Alarms = std::vector<Alarm>;

struct MyAlarm : public Alarm {
  std::string owner;

  MyAlarm() = default;
  MyAlarm& operator=(const Alarm& other) {
    this->alarm_type = other.alarm_type;
    this->device_id = other.device_id;
    this->additional_information = other.additional_information;

    return *this;
  }
  explicit MyAlarm(const Alarm& other) {
    *this = other;
  }
};

struct MyAlarms : public std::vector<MyAlarm> {
  void operator=(const Alarms& other) {
    for (const auto& other_alarm : other) {
      this->push_back(MyAlarm{other_alarm});
    }
  }
  explicit MyAlarms(const Alarms& other) {
    *this = other;
  }
};

void alarm_fun(MyAlarms alarms) {
  for (const auto& alarm : alarms) {
    std::cout << "alarm.device_id" << alarm.alarm_type << "\n";
  }
}

//-------------------------------------------------------------------------------
int main() {
  // SensorChannelExample();
  Alarm a;
  MyAlarm ma1 = static_cast<MyAlarm>(a);   // static_cast is necessary
  MyAlarm ma{a};
  ma = a;
  ma.operator=(a);

  Alarms alarms;
  // alarm_fun(alarms);                         // static_cast is necessary
  alarm_fun(static_cast<MyAlarms>(alarms));

  return 0;
}
