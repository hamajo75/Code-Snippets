#include <iostream>
#include <string.h>
#include <memory>

//-------------------------------------------------------------------------------
class MessageHandler {
 public:
  void AddReceiveAddresses(std::initializer_list<std::string> addresses){}
};
//-------------------------------------------------------------------------------
class MessageClient {
 public:
  MessageClient& AddConnection(std::string url) {
    // create proton::messaging_handler for this connection
    // add it to the collection
    return *this;
  }
  MessageHandler& AddMessageHandler(const std::weak_ptr<MessageHandler>& message_handler) {
    return *message_handler.lock();
  }
};
//-------------------------------------------------------------------------------
int main() {
  // MessageHandler message_handler;

  auto message_handler {std::make_shared<MessageHandler>()};

  MessageClient message_client;

  message_client.AddConnection("//127.0.0.1:5672")
                .AddMessageHandler(message_handler)
                 .AddReceiveAddresses({
                    "intercom_daemon_receive",
                    "workplace_alarms"});

  message_client.AddConnection("//52.157.151.140:5671")
                .AddMessageHandler(message_handler)
                .AddReceiveAddresses({
                  "workplace_receive"});

                  // .options()
                  //   .user("USER")
                  //   .password("PASSWORD")
                  //   .ssl_certificate("CLIENT_CERTIFICATE", "CLIENT_PRIVATE_KEY", "BROKER_CERTIFICATE")
                  // .AddMessageHandler(message_handler)
                  //   .AddReceiveAddresses({
                  //   "workplace_receive"});
  return 0;
}
