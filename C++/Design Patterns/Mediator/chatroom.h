#pragma once
#include "person.h"
#include <memory>

struct ChatRoom
{
  std::vector<std::weak_ptr<Person>> people; // assume append-only

  void join(std::weak_ptr<Person> p);
  void broadcast(const std::string& origin, const std::string& message);
  void message(const std::string& origin,
      const std::string& who,
      const std::string& message);
};
