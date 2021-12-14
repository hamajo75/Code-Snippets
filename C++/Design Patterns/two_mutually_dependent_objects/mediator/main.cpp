#include <iostream>
#include <string>

class Mediator;
class WebSocket {
 private:
  Mediator* mediator_;

 public:
  explicit WebSocket(Mediator* mediator) : mediator_{mediator} {}
  void Send(const std::string& msg);
  void Receive(const std::string& msg) {
    std::cout << "WebSocket::Receive: " << msg << "\n";
  }
  void Inject(const std::string& msg) {
    Send(msg);
  }
};

class MessageHandler {
 private:
  Mediator* mediator_;

 public:
  explicit MessageHandler(Mediator* mediator) : mediator_{mediator} {}
  void Send(const std::string& msg);
  void Receive(const std::string& msg) {
    std::cout << "MessageHandler::Receive: " << msg << "\n";
  }
  void Inject(const std::string& msg) {
    Send(msg);
  }
};

class Mediator {
 private:
  WebSocket websocket_;
  MessageHandler msg_handler_;
 public:
  Mediator() : websocket_{this}, msg_handler_{this} {}

  void SendToWebSocket(const std::string& msg) {
    websocket_.Receive(msg);
  }
  void SendToMessageHandler(const std::string& msg) {
    msg_handler_.Receive(msg);
  }

  void InjectStringFromWebsocket(const std::string& msg) {
    websocket_.Inject(msg);
  }
  void InjectMessage(const std::string& msg) {
    msg_handler_.Inject(msg);
  }
};

void WebSocket::Send(const std::string& msg) {
  mediator_->SendToMessageHandler(msg);
}

void MessageHandler::Send(const std::string& msg) {
  mediator_->SendToWebSocket(msg);
}

//-------------------------------------------------------------------------------
int main() {
  Mediator m;

  m.InjectMessage("message");
  m.InjectStringFromWebsocket("string");

  return 0;
}
