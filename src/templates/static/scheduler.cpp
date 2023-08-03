#include "scheduler.h"
#include "thread.h"
#include <iostream>
#include <syncstream>

using namespace PNtalk;

Scheduler PNtalk::scheduler;

void PNtalk::Scheduler::schdule_no_mutex(const std::shared_ptr<Net::Transition> &transition) {
    auto parent = transition->top_parent();
    for (auto i = _plan.begin(); i != _plan.end(); i++) {
        if (parent == (*i)->top_parent())
            return;
    }
    _plan.push_back(transition);
}

void PNtalk::Scheduler::schedule(const std::shared_ptr<Net::Transition> &transition) {
    // std::osyncstream(std::cout) << "scheduled: " << transition->name << std::endl;

    std::lock_guard<std::mutex> lk(m);

    schdule_no_mutex(transition);
}

void PNtalk::Scheduler::schedule(const std::set<std::shared_ptr<Net::Transition>> &transitions) {
    std::lock_guard<std::mutex> lk(m);
    // std::osyncstream(std::cout) << "scheduled: ";
    for (auto i : transitions) {
        schdule_no_mutex(i);
    }
}

void PNtalk::Scheduler::schedule(const std::deque<std::shared_ptr<Net::Transition>> &transitions) {
    std::lock_guard<std::mutex> lk(m);
    // std::osyncstream(std::cout) << "scheduled: ";
    for (auto i : transitions) {
        // std::osyncstream(std::cout) << i->name << " ";
        schdule_no_mutex(i);
    }
    // std::osyncstream(std::cout) << std::endl;
}

void PNtalk::Scheduler::run() {
    std::osyncstream(std::cerr) << "start" << std::endl;

    try {
        while (!_plan.empty() || !threads.empty()) {
            print_schedule();

            if (!_plan.empty())
                process_transition();

            if (!threads.empty())
                join_threads();

            // std::osyncstream(std::cout)<<"loop threads: "<<threads.size()<<std::endl;
        }

    } catch (std::exception &e) {
        while (!threads.empty())
            join_threads();
    }
    std::osyncstream(std::cerr) << "end" << std::endl;
}

std::shared_ptr<Net::Transition> PNtalk::Scheduler::pop() {
    std::lock_guard<std::mutex> lk(m);
    auto transition = _plan.front();

    _plan.pop_front();

    return transition;
}

void PNtalk::Scheduler::print_schedule() {
    std::lock_guard<std::mutex> lk(m);
    std::osyncstream cout(std::cerr);
    if (_plan.size()) {
        cout << "Schedule: ";
        for (auto &i : _plan)
            cout << i->name << " ";
        cout << std::endl;
    }
}

void PNtalk::Scheduler::join_threads() {
    for (auto it = threads.begin(); it != threads.end();) {
        if (it->try_join()) {
            it = threads.erase(it);
        } else
            it++;
    }
}

void PNtalk::Scheduler::process_transition() {
    auto transition = pop();

    // std::osyncstream(std::cout) << "Trans: " << transition.use_count() << std::endl;
    if (!transition->scheduler_check())
        return;

    // std::osyncstream(std::cout) << "Executing: " << transition->name << std::endl;
    threads.push_back(std::move(TransitionThread(transition)));
    threads.back().run();
}
