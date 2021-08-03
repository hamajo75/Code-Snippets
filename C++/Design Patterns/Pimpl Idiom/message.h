#pragma once

#include <memory>
#include <string>

namespace Messaging {
//-----------------------------------------------------------------------------
class Message {
 private:
  class MessageImpl;
  std::unique_ptr<MessageImpl> impl_;

 public:
  explicit Message(const std::string& payload);

  // rule of 5 (see Scott Meyers Effective Modern C++ - Item 22)
  Message(const Message&);
  Message& operator=(const Message&);
  Message(Message&&);
  Message& operator=(Message&&);
  ~Message();
};

}  // namespace Messaging
