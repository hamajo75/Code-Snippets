#include <iostream>
#include <string.h>
#include <functional>
#include <memory>
#include <map>

using CallbackFunction = std::function<void(const std::string& msg)>;
//-------------------------------------------------------------------------------
class ICallback {
 public:
  virtual void Execute(const std::string& msg) = 0;
};
//-------------------------------------------------------------------------------
class Callback : public ICallback {
 private:
  CallbackFunction callback_function;
  std::string name_;

 public:
  explicit Callback(const std::string& name, CallbackFunction fun) :
    callback_function{std::move(fun)}, name_{name} {}

  void Execute(const std::string& msg) {
    std::cout << "executing " << name_ << " ";
    callback_function(msg);
  }
};
//-------------------------------------------------------------------------------
class CallbackCollection {
 private:
  std::map<std::string, std::unique_ptr<Callback>> callbacks_;
  // std::vector<std::unique_ptr<Callback>> callbacks_;

 public:
  void AddCallback(const std::string& name, const CallbackFunction& fun) {
    callbacks_[name] = std::make_unique<Callback>(name, fun);
  }

  void Call(const std::string& name, const std::string& param) {
    callbacks_[name]->Execute(param);
  }

  void CallThemAll(const std::string& param) {
    for (auto& [name, callback] : callbacks_) {
      callback->Execute(param);
    }
  }

  void Send() {
    std::cout << "sending \n";
  }
};
//-------------------------------------------------------------------------------
int main() {
  CallbackCollection callback_collection;
  int in_scope_value = 100;

  callback_collection.AddCallback("first",
    [=](std::string str) {
      std::cout << "Callback " << str << " " << in_scope_value <<"\n";
    }
  );

  callback_collection.AddCallback("second",
    [&](std::string str) {
      std::cout << "Callback " << str << "\n";
      callback_collection.Send();
    }
  );

  callback_collection.Call("first", "param");

  callback_collection.CallThemAll("with parameter");

  return 0;
}
