#include <iostream>
#include <string>

class Mediator;
class WebSocket {
 private:
  Mediator* mediator_;

 public:
  explicit WebSocket(Mediator* mediator) : mediator_{mediator} {}

  void Send(const std::string& msg) {
    mediator_->SendToMessageHandler(msg);
  }
};

class MessageHandler {
 private:
  Mediator* mediator_;

 public:
  explicit MessageHandler(Mediator* mediator) : mediator_{mediator} {}

  void Send(const std::string& msg) {
    mediator_->SendToWebSocket(msg);
  }
};

class Mediator {
 private:
  WebSocket websocket_;
  MessageHandler msg_handler_;
 public:
  Mediator() : websocket_{this}, msg_handler_{this} {}

  void SendToWebSocket(const std::string& msg) {
    websocket_.Send(msg);
  }
  void SendToMessageHandler(const std::string& msg) {
    msg_handler_.Send(msg);
  }
};

//-------------------------------------------------------------------------------
int main() {
  Mediator m;
  return 0;
}
