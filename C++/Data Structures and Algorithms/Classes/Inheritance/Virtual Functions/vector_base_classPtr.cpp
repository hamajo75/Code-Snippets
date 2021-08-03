#include <string.h>

#include <iostream>
#include <memory>
#include <vector>
#include <set>

//-----------------------------------------------------------------------------
// g++ -std=c++17 .\vector_base_classPtr.cpp
//-----------------------------------------------------------------------------
class Receiver {
 private:
  std::set<std::string>addresses_;

 public:
  Receiver() = default;
  virtual ~Receiver() = default;

  void SetAddresses(std::initializer_list<std::string> addresses) {
    addresses_.insert(addresses);
  }

  virtual void OnReceive() = 0;
};
//-----------------------------------------------------------------------------
class Client {
 private:
  std::vector<Receiver*> receivers_;

 public:
  Client() = default;
  virtual ~Client() = default;

  void AddReceiver(Receiver* receiver) {
    receivers_.push_back(receiver);
  }

  void receive() {
    for (const auto& receiver : receivers_)
      receiver->OnReceive();
  }
};
//-----------------------------------------------------------------------------
class WorkplaceMessageReceiver : public Receiver {
 public:
  WorkplaceMessageReceiver() {}

  void OnReceive() {
    std::cout << "receiving\n";
  }
};
//-----------------------------------------------------------------------------
std::vector<std::unique_ptr<Client>> clients_;
Client* CreateClient() {
  return clients_.emplace_back(std::make_unique<Client>()).get();
}
//-----------------------------------------------------------------------------
int main() {
  auto workplace_client = CreateClient();
  WorkplaceMessageReceiver workplace_message_receiver;
  workplace_message_receiver.SetAddresses({
                            "intercom_daemon_receive",
                            "workplace_alarms"});
  workplace_client->AddReceiver(&workplace_message_receiver);

  workplace_client->receive();
  return 0;
}