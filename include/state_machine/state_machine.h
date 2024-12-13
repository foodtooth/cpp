#ifndef CPP_STATE_MACHINE_STATE_MACHINE_H_
#define CPP_STATE_MACHINE_STATE_MACHINE_H_

#include <iostream>
#include <memory>
#include <optional>

namespace cpp::state_machine {
class StateMachine;
class State {
 public:
  virtual ~State() = default;

  virtual void onEntry(StateMachine& fsm) = 0;
  virtual void onExit(StateMachine& fsm) = 0;
  virtual std::optional<std::shared_ptr<State>> handleEvent(
      StateMachine& fsm, const std::string& event) = 0;
};

class StateMachine {
 public:
  StateMachine(std::shared_ptr<State> initialState)
      : currentState(std::move(initialState)) {
    currentState->onEntry(*this);
  }

  void handleEvent(const std::string& event) {
    auto nextState = currentState->handleEvent(*this, event);
    if (nextState) {
      currentState->onExit(*this);
      currentState = std::move(*nextState);
      currentState->onEntry(*this);
    }
  }

 private:
  std::shared_ptr<State> currentState;
};

class Sleeping : public State {
 public:
  void onEntry(StateMachine& fsm) override {
    std::cout << "Entering Sleeping State\n";
  }

  void onExit(StateMachine& fsm) override {
    std::cout << "Exiting Sleeping State\n";
  }

  std::optional<std::shared_ptr<State>> handleEvent(
      StateMachine& fsm, const std::string& event) override;

 private:
  bool canWakeUp() {
    // Implement your guard logic here
    return true;  // For demonstration, always return true
  }
};

class Awake : public State {
 public:
  void onEntry(StateMachine& fsm) override {
    std::cout << "Entering Awake State\n";
  }

  void onExit(StateMachine& fsm) override {
    std::cout << "Exiting Awake State\n";
  }

  std::optional<std::shared_ptr<State>> handleEvent(
      StateMachine& fsm, const std::string& event) override {
    if (event == "Sleep") {
      return std::make_shared<Sleeping>();
    }
    return std::nullopt;  // Stay in the same state
  }
};

std::optional<std::shared_ptr<State>> Sleeping::handleEvent(
    StateMachine& fsm, const std::string& event) {
  if (event == "WakeUp") {
    // Check guard condition before transitioning
    if (canWakeUp()) {
      return std::make_shared<Awake>();
    }
  }
  return std::nullopt;  // Stay in the same state
}
}  // namespace cpp::state_machine

#endif /* CPP_STATE_MACHINE_STATE_MACHINE_H_ */