#pragma once
#include "net_PN.h"
#include "net_transition.h"
#include <list>
#include <memory>
#include <mutex>
#include <set>

namespace PNtalk {

class Scheduler {
    std::mutex m;

  public:
    void schedule(const std::shared_ptr<Net::Transition> &transition);
    void schedule(const std::set<std::shared_ptr<Net::Transition>> &transitions);
    void schedule(const std::deque<std::shared_ptr<Net::Transition>> &transitions);
    std::shared_ptr<Net::Transition> pop();
    void run();

    void join_threads();
    void process_transition();

    void print_schedule();

  private:
    void schdule_no_mutex(const std::shared_ptr<Net::Transition> &transition);
    class TransitionThread;
    std::list<std::shared_ptr<Net::Transition>> _plan;
    std::list<TransitionThread> threads;
};

extern Scheduler scheduler;

} // namespace PNtalk
