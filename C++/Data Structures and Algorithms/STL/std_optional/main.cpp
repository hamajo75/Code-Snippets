#include <iostream>
#include <string>

#include <optional>

void Simple() {
  std::optional<int> i;
  // i = 1;

  if (i)
    std::cout << i.value();

  // use default value
  std::cout << i.value_or(2);
}

struct MessageHeader {
  std::string MessageType;
  std::optional<std::string> MessageVersion;
  std::optional<std::string> CreatedAt;
  std::optional<std::string> MessageId;
  std::optional<std::string> ValidUntil;
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

int main() {
  Simple();

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
