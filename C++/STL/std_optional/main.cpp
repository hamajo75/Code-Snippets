#include <iostream>
#include <string>

#include <optional>
#include <vector>

void Simple() {
  std::optional<int> i;
  // i = 1;

  if (i.value_or(0) == 0)
    std::cout << "this is not ok\n";

  if (i) {
    std::cout << i.value() << "\n";             // .value()
    std::cout << *i << "\n";             // pointer style
  }

  // use default value
  std::cout << i.value_or(2) << "\n";
}

struct SensorChannel {
    int64_t ChannelNumber;
    std::string GasType;
};

struct MessageHeader {
  std::string MessageType;
  std::optional<std::string> MessageVersion;
  std::optional<std::string> CreatedAt;
  std::optional<std::string> MessageId;
  std::optional<std::string> ValidUntil;
  std::optional<SensorChannel> sensor_channel;
};

struct ConnectionOptions {
  struct Credentials {
    std::string user;
    std::string password;
  };
  std::optional<Credentials> credentials;
  struct SSL {
    std::string ssl_client_certificate;
    std::string ssl_client_private_key;
    std::string ssl_broker_certificate;
  } ssl;
  bool reconnect;
};

void OptionalStruct() {
  MessageHeader msg_header{"type", "created_at"};
  SensorChannel sensor_channel{0, "CO2"};
  msg_header.sensor_channel = sensor_channel;

  std::cout << "msg_header.sensor_channel.value().GasType " << msg_header.sensor_channel->GasType << "\n";

  MessageHeader msg_header2{"type", "created_at"};
  // method 1
  msg_header2.sensor_channel = SensorChannel{msg_header.sensor_channel.value().ChannelNumber,         // .value()
                                            msg_header.sensor_channel->GasType};                     // pointer style
  // method 2
  msg_header2.sensor_channel.emplace(SensorChannel{msg_header.sensor_channel.value().ChannelNumber,
                                                  msg_header.sensor_channel.value().GasType});

  std::cout << "msg_header2.SensorChannel.value().GasType " << msg_header2.sensor_channel.value().GasType << "\n";
}

struct PairingDevice {
    std::optional<std::string> device_id;
    std::optional<std::string> device_type;
    std::string hardware_id;
    std::string pairing_status;
};

struct Intercom {
    std::optional<std::string> device_id;
    std::string hardware_id;
    std::optional<bool> is_master;
    std::optional<std::vector<PairingDevice>> pairing_devices;
    std::string pairing_status;
};

void TestOptionalVector() {
  Intercom wimp_intercom;

  std::vector<PairingDevice> pairing_devices;
  std::optional<std::vector<PairingDevice>> pairing_devices_opt;
  for (int i = 0; i < 10; ++i) {
    PairingDevice device;
    device.hardware_id = std::to_string(i);
    pairing_devices_opt->push_back(device);          // beware! pairing_devices == std::nullopt
    pairing_devices.push_back(device);
  }
  wimp_intercom.pairing_devices = pairing_devices;

  pairing_devices_opt.value()[0].pairing_status;

  for (auto device : wimp_intercom.pairing_devices.value()) {
    std::cout << device.hardware_id << "\n";
  }
}

int main() {
  Simple();
  // OptionalStruct();
  // TestOptionalVector();

  return 0;
}
