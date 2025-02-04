#pragma once

#include <sstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include "core/NodeVisitor.h"
#include <vector>

class GizmoDumper : public NodeVisitor{
public:
  GizmoDumper(std::ostringstream& dumpstream) : dumpstream(dumpstream) {

  }

  Response visit(State& state, const AbstractNode& node) override;
  // Response visit(State& state, const GroupNode& node) override;
  // Response visit(State& state, const ListNode& node) override;
  // Response visit(State& state, const RootNode& node) override;

private:
  // std::shared_ptr<const AbstractNode> root;
  // std::ostringstream dumpstream;

  // std::stack<std::string> stringStack;
  std::vector<std::string> stringStack;
  std::ostringstream& dumpstream;
};


