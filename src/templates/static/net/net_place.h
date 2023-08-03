#pragma once

#include "boolean.h"
#include "integer.h"
#include "net_multiset.h"
#include "net_net.h"
#include "object_base.h"
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <set>

namespace PNtalk {

class Net::Place {
  public:
    std::deque<MultiSetItem> _values;
    Place();
    Place(const MultiSet &init);
    Place(Place &&other);
    std::mutex m;
    std::condition_variable cv;

    bool match(std::weak_ptr<Net::Transition> trans, const MultiSet &edge_expr);
    bool pop(std::weak_ptr<Net::Transition> trans, const MultiSet &edge_expr);
    void push(const MultiSet &edge_expr);

    void update();

  protected:
    struct transitions_compare {
        bool operator()(const std::weak_ptr<Net::Transition> &lhs, const std::weak_ptr<Net::Transition> &rhs) const;
    };
    std::set<std::weak_ptr<Net::Transition>, transitions_compare> _update_transitions;
    void schedule(std::shared_ptr<Net::Transition> trans);
    void link_to_transition(std::weak_ptr<Net::Transition> trans);
};

} // namespace PNtalk
