#include <iostream>
#include <string>
#include <memory>

class MessageHandler;
class WebSocket {
 private:
  std::weak_ptr<MessageHandler> msg_handler_;

 public:
  WebSocket() = default;
  void SetMessageHandler(std::weak_ptr<MessageHandler>);

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
  std::weak_ptr<WebSocket> websocket_;

 public:
  MessageHandler() = default;
  void SetWebSocket(std::weak_ptr<WebSocket>);

  void Send(const std::string& msg);
  void Receive(const std::string& msg) {
    std::cout << "MessageHandler::Receive: " << msg << "\n";
  }
  void Inject(const std::string& msg) {
    Send(msg);
  }
};

void WebSocket::SetMessageHandler(std::weak_ptr<MessageHandler> msg_handler) {
  msg_handler_ = msg_handler;
}

void WebSocket::Send(const std::string& msg) {
  if (auto spt = msg_handler_.lock())
    spt->Receive(msg);
}

void MessageHandler::SetWebSocket(std::weak_ptr<WebSocket> websocket) {
  websocket_ = websocket;
}
void MessageHandler::Send(const std::string& msg) {
  if (auto spt = websocket_.lock())
    spt->Receive(msg);
}

//-------------------------------------------------------------------------------
int main() {
  auto msg_handler = std::make_shared<MessageHandler>();
  auto websocket = std::make_shared<WebSocket>();

  msg_handler->SetWebSocket(websocket);
  websocket->SetMessageHandler(msg_handler);

  msg_handler->Inject("message");
  websocket->Inject("string");

  return 0;
}
