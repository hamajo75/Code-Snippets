#include <iostream>
#include <string>

#include <optional>

void Simple() {
  std::optional<int> i;
  // i = 1;

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
  std::optional<SensorChannel> SensorChannel;
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
  msg_header.SensorChannel = sensor_channel;

  std::cout << "msg_header.SensorChannel.value().GasType " << msg_header.SensorChannel->GasType << "\n";

  MessageHeader msg_header2{"type", "created_at"};
  // method 1
  msg_header2.SensorChannel = SensorChannel{msg_header.SensorChannel.value().ChannelNumber,         // .value()
                                            msg_header.SensorChannel->GasType};                     // pointer style
  // method 2
  msg_header2.SensorChannel.emplace(SensorChannel{msg_header.SensorChannel.value().ChannelNumber,
                                                  msg_header.SensorChannel.value().GasType});

  std::cout << "msg_header2.SensorChannel.value().GasType " << msg_header2.SensorChannel.value().GasType << "\n";
}

int main() {
  Simple();
  OptionalStruct();
  MessageHeader msg_header {"type", "created_at"};

  ConnectionOptions conn_opts {
     (ConnectionOptions::Credentials){    // here you cannot use plain initializer list
      "user",
      "password"
    },
    {                             // this works
      "ssl_client_certificate"
      "ssl_client_private_key"
      "ssl_broker_certificate"
    },
    true
  };

  return 0;
}
