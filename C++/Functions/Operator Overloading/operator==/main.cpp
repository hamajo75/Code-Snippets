#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>

struct VisibleDevice {
  std::string pairing_status;
};

bool operator==(const VisibleDevice& lhs, const VisibleDevice& rhs) {return false;}

struct GasDetector : public VisibleDevice {
  std::string gas_detector_status;
};

struct SensorChannel {
  int64_t channel_number = 0;
  std::string gas_type;
};

struct Alarm {
  std::optional<std::string> additional_information = std::nullopt;
  std::string alarm_type;
  std::optional<std::string> device_id = std::nullopt;
  std::optional<SensorChannel> sensor_channel = std::nullopt;
};

using Alarms = std::vector<Alarm>;

bool operator==(const Alarm& lhs, const Alarm& rhs) {
  auto ret = (lhs.alarm_type == rhs.alarm_type &&
              lhs.device_id == rhs.device_id &&
              lhs.additional_information == rhs.additional_information);

  if (ret && lhs.sensor_channel && rhs.sensor_channel) {
    return (lhs.sensor_channel->channel_number == rhs.sensor_channel->channel_number &&
            lhs.sensor_channel->gas_type == rhs.sensor_channel->gas_type);
  }

  return ret;
}

bool IsAlarmStateChanged(const Alarms& a, const Alarms& b) {
  return std::is_permutation(a.begin(), a.end(),
                              b.begin());
}

//-------------------------------------------------------------------------------
int main() {
  GasDetector a;
  GasDetector b;

  if (a == b)
    std::cout << "comparison true\n";
  else
    std::cout << "comparison false\n";

  Alarm a1{"", "", "", SensorChannel{1, ""}};
  Alarm a2;
  Alarms alarms1;
  Alarms alarms2;
  alarms1.push_back(a1);
  alarms2.push_back(a2);

  if (IsAlarmStateChanged(alarms1, alarms2))
    std::cout << "equal\n";
  else
    std::cout << "not equal\n";

  return 0;
}
