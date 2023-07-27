#include "net_transition.h"
#include "net_place.h"

bool PNtalk::PN::Transition::match(const std::string &place, const MultiSet &multiset) {
    if (_places.find(place) == _places.end())
        return false;

    auto locked = _places[place].lock();
    if (_places[place].expired())
        return false;

    return locked->match(weak_from_this(), multiset);
}

bool PNtalk::PN::Transition::pop(const std::string &place, const MultiSet &multiset) {
    if (_places.find(place) == _places.end())
        return false;

    auto locked = _places[place].lock();
    if (_places[place].expired())
        return false;

    return locked->pop(weak_from_this(), multiset);
}

bool PNtalk::PN::Transition::push(const std::string &place, const MultiSet &multiset) {
    if (_places.find(place) == _places.end())
        return false;

    auto locked = _places[place].lock();
    if (_places[place].expired())
        return false;

    locked->push(multiset);
}
