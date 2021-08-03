#include <iostream>
#include <string.h>
#include <set>
#include <initializer_list>
#include <map>

//-----------------------------------------------------------------------------
class Message : public std::string {
 private:
  const std::string message_;
  std::string routing_key_;
 public:
  explicit Message(const std::string& message, std::string routing_key) :
        message_(message), routing_key_(routing_key) {}

  std::string GetRoutingKey() { return routing_key_; }

  friend std::ostream& operator<<(std::ostream& out, const Message& msg) {
      return out << msg.message_;
  }
};
//-----------------------------------------------------------------------------
class MessageReceiver {
 public:
  virtual void OnReceive(Message message) = 0;
};
//-----------------------------------------------------------------------------
class MessageDispatcher {
 private:
  std::set<MessageReceiver*> receivers_;

 protected:
  void DispatchMessage(Message message) {
    for (auto receiver : receivers_) {
        receiver->OnReceive(message);
    }
  }

 public:
  void AddReceiver(MessageReceiver* msg_receiver) {
    receivers_.insert(msg_receiver);
  }
  void RemoveReceiver(MessageReceiver* msg_receiver) {
    receivers_.erase(msg_receiver);
  }
};
//-------------------------------------------------------------------------------
class MessageClient : public MessageDispatcher {
 public:
  virtual void Send(const std::string& url, const std::string& address, Message message) = 0;
  virtual void Request(const std::string& url,
               const std::string& send_address,
               const std::string& reply_to_address,
               Message message) = 0;
  virtual void Run() = 0;
};
//-------------------------------------------------------------------------------
class ProtonMessageClient : public MessageClient {
 public:
  void Send(const std::string& url, const std::string& address, Message message) {}
  void Request(const std::string& url,
               const std::string& send_address,
               const std::string& reply_to_address,
               Message message) {}

  void Run() {
    DispatchMessage(Message{"this is the message", "//127.0.0.1:5672"});
  }
};
//-------------------------------------------------------------------------------
class MessageHandler  : public MessageReceiver {
 private:
  // const std::string reply_to_address_ {""};
  std::map<std::string, std::string> addresses_;
  std::set<std::string>urls_;

 public:
  MessageHandler() {}
  void AddConnection(const std::string& url,
                            std::initializer_list<std::string> addresses) {
    urls_.insert(url);
    for (auto address : addresses)
      addresses_[address] = url;
  }

  virtual void OnReceive(Message message) = 0;
};
//-------------------------------------------------------------------------------
class MyMessageHandler : public MessageHandler {
 protected:
  void OnReceive(Message message) {
    std::cout << "MyMessageHandler::OnReceive\n";
    std::cout << "received: " << message << " on " << message.GetRoutingKey() << "\n";
  }

 public:
  MyMessageHandler() {}
};
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  MyMessageHandler msg_handler;
  ProtonMessageClient client;

  msg_handler.AddConnection("//127.0.0.1:5672",
                           {"gas_daemon/info/*",
                            "gas_daemon/errors",
                            "gas_daemon/requests"});
  msg_handler.AddConnection("//52.155.155.140:5671",
                           {"gas_daemon/requests/*"});

  client.AddReceiver(&msg_handler);
  client.Run();

  return 0;
}
