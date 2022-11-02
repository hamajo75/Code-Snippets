#include <cstddef>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <string>
#include <any>
#include <tuple>
#include <vector>

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

using EventParamsList = std::vector<std::any>;
using Events = std::vector<std::pair<Event, EventParamsList>>;
using EventHandler = std::function<void(EventParamsList)>;
using EventHandlers = std::unordered_map<Event, EventHandler>;

EventHandlers event_handlers_ = {
  {Event::kEventA, [](const EventParamsList& p){
    auto info = std::any_cast<std::string>(p[0]);
    std::cout << "handle EventA " << info << "\n"; }},
  {Event::kEventB, [](const EventParamsList& p){
    auto flag = std::any_cast<bool>(p[0]);
    std::cout << "handle EventB " << std::boolalpha << flag << "\n"; }},
  {Event::kEventC, [](const EventParamsList& p){
    std::cout << "handle EventC\n"; }},
  {Event::kEventE, [](const EventParamsList& p){}}
};

void OnUpdate(const Events& events) {
  for (const auto& [event, params] : events) {
    try {
      event_handlers_[event](params);
    } catch (const std::exception& e) {
      std::cout << "no handler found\n";
    }
  }
}

//-------------------------------------------------------------------------------
int main() {
  OnUpdate(
  {
    {Event::kEventA, {"info string", 1, 3.5}},
    {Event::kEventB, {true}},
    {Event::kEventC, {}}
  });

  return 0;
}
