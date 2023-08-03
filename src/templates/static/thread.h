#include "net_transition.h"
#include "scheduler.h"
#include <atomic>
#include <mutex>
#include <thread>

namespace PNtalk {
class Scheduler::TransitionThread {
  public:
    std::shared_ptr<Net::Transition> _transition;
    TransitionThread(std::shared_ptr<Net::Transition> transition);
    TransitionThread(TransitionThread &&old);
    void run();
    bool try_join();

  private:
    std::atomic<bool> finished{false};
    std::thread thread;
};

} // namespace PNtalk