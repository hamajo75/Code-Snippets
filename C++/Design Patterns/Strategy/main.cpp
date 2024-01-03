#include <iostream>
#include <memory>

// Strategy Interface
class Strategy {
public:
  virtual ~Strategy() {}
  virtual void execute() const = 0;
};

// Concrete Strategy A
class ConcreteStrategyA : public Strategy {
public:
  void execute() const override {
    std::cout << "Concrete Strategy A\n";
  }
};

// Concrete Strategy B
class ConcreteStrategyB : public Strategy {
public:
  void execute() const override {
    std::cout << "Concrete Strategy B\n";
  }
};

// Context
class Context {
private:
  std::unique_ptr<Strategy> strategy_;
public:
  Context(std::unique_ptr<Strategy> strategy) : strategy_(std::move(strategy)) {}
  void set_strategy(std::unique_ptr<Strategy> strategy) {
    strategy_ = std::move(strategy);
  }
  void execute_strategy() const {
    strategy_->execute();
  }
};

int main() {
  Context context(std::make_unique<ConcreteStrategyA>());
  context.execute_strategy(); // Outputs: "Concrete Strategy A"

  context.set_strategy(std::make_unique<ConcreteStrategyB>());
  context.execute_strategy(); // Outputs: "Concrete Strategy B"

  return 0;
}