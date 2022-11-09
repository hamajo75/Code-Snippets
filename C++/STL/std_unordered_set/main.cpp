#include <cstddef>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <string>
#include <any>
#include <tuple>

#include <unordered_map>
#include <unordered_set>
#include <functional>

enum class Event {
  kEventA,
  kEventB,
  kEventC,
  kEventD,
  kEventE
};

using EventGroup = std::unordered_set<Event>;
using EventHandlerParams = std::initializer_list<std::any>;
using EventHandler = std::function<void(EventHandlerParams)>;
using EventHandlers = std::unordered_map<Event, EventHandler>;

EventHandlers event_handlers_ = {
  {Event::kEventA,
    [](EventHandlerParams p){
    auto info = std::any_cast<std::string>(*p.begin());
    std::cout << "handle EventA " << info << "\n"; }

    },
  {Event::kEventB, [](EventHandlerParams p){
    auto flag = std::any_cast<bool>(*p.begin());
    std::cout << "handle EventB " << std::boolalpha << flag << "\n"; }},
  {Event::kEventC, [](EventHandlerParams p){ std::cout << "handle EventC\n"; }},
  {Event::kEventE, [](EventHandlerParams p){}}
};

void OnUpdate(
  std::string info,
  bool flag,
  EventGroup events
) {
  for (const auto& event : events) {
    try {
      if (event == Event::kEventA)
        event_handlers_[event]({info});
      if (event == Event::kEventB)
        event_handlers_[event]({flag});
    } catch (const std::exception& e) {
      std::cout << "no handler found\n";
    }
  }
}

//-------------------------------------------------------------------------------
int main() {
  OnUpdate(
  "info", true,
  {
    Event::kEventA,
    Event::kEventB,
    Event::kEventC,
    Event::kEventD,
    Event::kEventD
  });

  return 0;
}
