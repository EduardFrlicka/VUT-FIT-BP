#include "thread.h"
#include <iostream>
#include <syncstream>

PNtalk::Scheduler::TransitionThread::TransitionThread(TransitionThread &&old) : TransitionThread(old._transition){};

PNtalk::Scheduler::TransitionThread::TransitionThread(std::shared_ptr<Net::Transition> transition) : _transition(transition){};

bool PNtalk::Scheduler::TransitionThread::try_join() {
    if (!finished.load())
        return false;

    thread.join();
    return true;
}

void PNtalk::Scheduler::TransitionThread::run() {
    thread = std::thread([&] {
        // std::osyncstream(std::cout) << "    Started: " << _transition->name << std::endl;
        _transition->scheduler_execute();
        // std::osyncstream(std::cout) << "    Finished: " << _transition->name << std::endl;
        _transition.reset();
        finished.store(true);
    });
}
