#pragma once
#include <string>
#include <iostream>
#include <vector>

struct ChatRoom;

struct Person
{
  std::string name;
  ChatRoom* room = nullptr;
  std::vector<std::string> chat_log;

  Person(const std::string& name);

  void say(const std::string& message) const;
  void privateMessaging(const std::string& who, const std::string& message) const;
  void receive(const std::string& origin, const std::string& message);
};
