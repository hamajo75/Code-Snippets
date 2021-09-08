
#include "chatroom.h"
#include <algorithm>

void ChatRoom::broadcast(const std::string& origin, const std::string& message) {
  for (auto p : people)
    if (auto spt = p.lock()) {
      if (spt->name != origin)
        spt->receive(origin, message);
    }
}

void ChatRoom::join(std::weak_ptr<Person> p) {
  std::string join_msg;

  if (auto spt = p.lock())
    join_msg = spt->name + " joins the chat";
  
  broadcast("room", join_msg);

  if (auto spt = p.lock())
    spt->room = this;

  people.push_back(p);
}

void ChatRoom::message(const std::string& origin,
  const std::string& who,
  const std::string& message) {
  auto target = find_if(begin(people), end(people), [&](std::weak_ptr<Person> p) { 
    if (auto spt = p.lock())
      return spt->name == who;
    return false;
    });

  if (target != end(people)) {
    if (auto spt = (*target).lock())
      spt->receive(origin, message);
  }
}
