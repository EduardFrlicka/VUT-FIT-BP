#include "net_net.h"
#include "object_base.h"
#include "scheduler.h"
#include <memory>

PNtalk::Net::Net() {
}

PNtalk::Net::Net(Places places) : _places(places){};

void PNtalk::Net::add_place(std::string name, std::shared_ptr<Place> place) {
    _local_places.push_back(place);
    _places[name] = place;
}

void PNtalk::Net::add_transition(std::shared_ptr<Transition> transition) {
    transitions.push_back(transition);
}
void PNtalk::Net::schedule() {
    scheduler.schedule(transitions);
}

void PNtalk::Net::distribute_self(std::weak_ptr<Object> this_obj) {
    for (auto &trans : transitions)
        trans->this_obj = this_obj;
}

std::shared_ptr<PNtalk::Net::Place> PNtalk::Net::place(const std::string &name) {
    return _places[name].lock();
}