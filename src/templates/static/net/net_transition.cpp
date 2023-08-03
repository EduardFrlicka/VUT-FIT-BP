#include "net_transition.h"
#include "net_place.h"
#include "scheduler.h"

PNtalk::Net::Transition::Transition(Places places) : _places(places){};
PNtalk::Net::Transition::Transition(Places places, std::weak_ptr<Transition> parent) : _parent(parent), _places(places){};

bool PNtalk::Net::Transition::match(const std::string &place, const MultiSet &multiset) {
    if (_places.find(place) == _places.end())
        return false;

    auto locked = _places[place].lock();
    if (_places[place].expired())
        return false;

    return locked->match(weak_from_this(), multiset);
}

bool PNtalk::Net::Transition::pop(const std::string &place, const MultiSet &multiset) {
    if (_places.find(place) == _places.end())
        return false;

    auto locked = _places[place].lock();
    if (_places[place].expired())
        return false;

    return locked->pop(weak_from_this(), multiset);
}

void PNtalk::Net::Transition::push(const std::string &place, const MultiSet &multiset) {
    if (_places.find(place) == _places.end())
        return;

    auto locked = _places[place].lock();
    if (_places[place].expired())
        return;

    locked->push(multiset);
}

std::shared_ptr<PNtalk::Net::Transition> PNtalk::Net::Transition::top_parent() {
    auto locked = _parent.lock();
    if (locked)
        return locked->top_parent();

    return shared_from_this();
};

bool PNtalk::Net::Transition::scheduler_check() {
    return check();
}

bool PNtalk::Net::Transition::scheduler_execute() {
    bool res = execute();
    if (res)
        scheduler.schedule(this->copy());
    return res;
}
