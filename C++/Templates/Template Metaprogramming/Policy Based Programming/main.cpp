#include <iostream>
#include <string>

template <typename OutputPolicy, typename LanguagePolicy>
class HelloWorld : private OutputPolicy, private LanguagePolicy {
 public:
  // Behavior method.
  void Run() const {
    // Two policy methods.
    Print(Message());
  }

 private:
  using LanguagePolicy::Message;
  using OutputPolicy::Print;
};

class OutputPolicyWriteToCout {
 protected:
  template <typename MessageType>
  void Print(MessageType&& message) const {
    std::cout << message << std::endl;
  }
};

class LanguagePolicyEnglish {
 protected:
  std::string Message() const { return "Hello, World!"; }
};

class LanguagePolicyGerman {
 protected:
  std::string Message() const { return "Hallo Welt!"; }
};

int main() {
  // Example 1
  using HelloWorldEnglish = HelloWorld<OutputPolicyWriteToCout, LanguagePolicyEnglish>;

  HelloWorldEnglish hello_world;
  hello_world.Run();  // Prints "Hello, World!".

  // Example 2
  // Does the same, but uses another language policy.
  using HelloWorldGerman = HelloWorld<OutputPolicyWriteToCout, LanguagePolicyGerman>;

  HelloWorldGerman hello_world2;
  hello_world2.Run();  // Prints "Hallo Welt!".
}