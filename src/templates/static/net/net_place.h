#pragma once

#include "boolean.h"
#include "integer.h"
#include "net_PN.h"
#include "object_base.h"

#include <deque>
#include <memory>
#include <set>

namespace PNtalk {

class MultiSetItem;

class MultiSetList {
    std::deque<std::shared_ptr<Object>> values;
};

class MultiSetItem {
  public:
    Integer _count;
    std::shared_ptr<Object> _value;

    MultiSetItem(const std::shared_ptr<Object> &value);
    MultiSetItem(const Integer &count, const std::shared_ptr<Object> &value);
};

class MultiSet : public std::deque<MultiSetItem> {};

class PN::Place {
    std::deque<Object> values;

    bool match(std::weak_ptr<PN::Transition> trans, const MultiSet &edge_expr);
    bool pop(std::weak_ptr<PN::Transition> trans, const MultiSet &edge_expr);
    void push(const MultiSet &edge_expr);

    void update();
    void schedule(std::shared_ptr<PN::Transition> trans);

  private:
    std::set<std::weak_ptr<PN::Transition>> update_transitions;
};
  
} // namespace PNtalk
