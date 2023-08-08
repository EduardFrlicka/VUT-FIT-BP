#include "net_place.h"
#include "object.h"
#include "scheduler.h"
#include <syncstream>

PNtalk::Net::Place::Place(){};
PNtalk::Net::Place::Place(const Place &other) : _values(other._values), m(), _update_transitions(other._update_transitions){};
PNtalk::Net::Place::Place(const MultiSet &init) : _values(init.values){};

bool PNtalk::PN::Place::match(std::weak_ptr<PN::Transition> trans, const MultiSet &edge_expr) {
    std::lock_guard<std::mutex> lk(m);
    link_to_transition(trans);

    auto left = _values.begin();
    auto right = edge_expr.values.begin();

    for (; left != _values.end() && right != edge_expr.values.end(); left++, right++)
        if (!left->match(*right))
            return false;

    if (right != edge_expr.values.end())
        return false;

    return true;
}

bool PNtalk::PN::Place::pop(std::weak_ptr<PN::Transition> trans, const MultiSet &edge_expr) {
    std::lock_guard<std::mutex> lk(m);
    link_to_transition(trans);

    auto left = _values.begin();
    auto right = edge_expr.values.begin();

    for (; left != _values.end() && right != edge_expr.values.end(); right++) {
        if (!left->match(*right))
            return false;
        left = _values.erase(left);
    }

    update();
    return true;
}

void PNtalk::PN::Place::push(const MultiSet &edge_expr) {
    {
        std::lock_guard<std::mutex> lk(m);

        for (auto &elem : edge_expr.values) {
            _values.push_back(elem);
        }
    }
    cv.notify_all();

    update();
}

void PNtalk::PN::Place::update() {
    std::deque<std::weak_ptr<PN::Transition>> expired;
    std::set<std::string> scheduled;
    // std::osyncstream cout(std::cout);

    // cout << "link              checked " << _update_transitions.size() << " ";

    for (auto trans : _update_transitions) {
        auto locked = trans.lock();

        if (trans.expired()) {
            expired.push_back(trans);
            continue;
        }

        if (scheduled.find(locked->name) != scheduled.end())
            continue;
        scheduled.insert(locked->name);

        // cout << locked->name << " ";
        schedule(locked);
    }
    // cout << std::endl;

    // std::cout << "link              erased " << expired.size() << std::endl;
    for (auto trans : expired)
        _update_transitions.erase(trans);
}

/**
 * @link https://stackoverflow.com/questions/32668742/a-set-of-weak-ptr
 */
bool PNtalk::Net::Place::transitions_compare::operator()(const std::weak_ptr<Net::Transition> &lhs, const std::weak_ptr<Net::Transition> &rhs) const {
    auto lptr = lhs.lock(), rptr = rhs.lock();
    if (!rptr)
        return false; // nothing after expired pointer
    if (!lptr)
        return true;  // every not expired after expired pointer
    return lptr.get() < rptr.get();
}

void PNtalk::Net::Place::schedule(std::shared_ptr<Net::Transition> trans) {
    scheduler.schedule(trans->copy());
}

void PNtalk::Net::Place::link_to_transition(std::weak_ptr<Net::Transition> trans) {
    auto locked = trans.lock();
    if (!locked)
        return;
    // std::cout << "linking " << locked->name << std::endl;
    if (_update_transitions.find(locked->top_parent()) != _update_transitions.end())
        return;

    _update_transitions.insert(locked->top_parent());
}
