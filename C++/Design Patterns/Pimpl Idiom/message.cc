#include <message.h>

namespace Messaging {
//--------------------------------------------------------------------------------
class Message::MessageImpl {
 private:
  std::string message_;

 public:
  explicit MessageImpl(const std::string& payload) : message_{payload} {}
};
//-----------------------------------------------------------------------------
Message::Message(const std::string& payload) :
  impl_{std::make_unique<MessageImpl>(payload)} {}
//-----------------------------------------------------------------------------
Message::Message(const Message& message) :
  impl_{std::make_unique<MessageImpl>(*message.impl_)} {}
//-----------------------------------------------------------------------------
Message& Message::operator=(const Message& message) {
  *impl_ = *message.impl_;
  return *this;
}
//-----------------------------------------------------------------------------
Message::Message(Message&& message) = default;
//-----------------------------------------------------------------------------
Message& Message::operator=(Message&& message) = default;
//-----------------------------------------------------------------------------
Message::~Message() = default;

}  // namespace Messaging