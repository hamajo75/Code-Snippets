#include <iostream>
#include <string.h>

#include <variant>
#include <optional>
//-------------------------------------------------------------------------------
struct event_connect {std::string_view address;};
struct event_connected {};
struct event_disconnect {};
struct event_timeout {};

using event = std::variant<event_connect, event_connected, event_disconnect, event_timeout>;
//-------------------------------------------------------------------------------
struct state_idle {};
struct state_connecting {
  static constexpr int n_max = 3;
  int n = 0;
  std::string address;
};
struct state_connected {};

using state = std::variant<state_idle, state_connecting, state_connected>;
//-------------------------------------------------------------------------------
struct Transitions {
  std::optional<state> operator()(state_idle,
                             const event_connect& e)
  { return state_connecting{std::string(e.address)}; }
  std::optional<state> operator()(state_connecting,
                             const event_connected& e)
  { return state_connected{}; }
  std::optional<state> operator()(state_connecting& s,
                             const event_timeout& e)
  { return ++s.n < state_connecting::n_max ? std::nullopt :
                                             std::optional<state>(state_idle{}); }
  std::optional<state> operator()(state_connected,
                             const event_disconnect& e)
  { return state_idle{}; }

  // default
  template<typename State, typename Event>
  std::optional<state> operator()(State&, const Event&) const
  { return std::nullopt;}
};
//-------------------------------------------------------------------------------
template<typename StateVariant, typename EventVariant, typename Transitions>
class FSM {
  StateVariant state_;
 public:
  void dispatch(const EventVariant& event) {
    std::optional<StateVariant> new_state = std::visit(Transitions{}, state_, event);
    if (new_state)
      state_ = *std::move(new_state);
  }
};

using ConnectionFSM = FSM<state, event, transitions>;
//-------------------------------------------------------------------------------
// testing
template<typename Fsm, typename... Events>
void dispatch(Fsm& fsm, Events&&... events) {
  (fsm.dispatch(std::forward<Evnts>(events)), ...)
}
//-------------------------------------------------------------------------------
int main() {
  ConnectionFSM fsm;

  dispatch( fsm,
            event_connect{"address"},
            event_timeout{},
            event_connected{},
            event_disconnect{}
  );

  return 0;
}
