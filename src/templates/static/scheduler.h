#pragma once
#include "net_transition.h"
#include <deque>
#include <mutex>
#include <set>

namespace PNtalk {

class Scheduler {
    std::deque<std::shared_ptr<PN::Transition>> _plan;

  public:
    void schedule(const std::set<std::shared_ptr<PN::Transition>> &transitions);
    void run();
};

extern Scheduler scheduler;

} // namespace PNtalk
