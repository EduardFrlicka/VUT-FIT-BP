#include "net_sync_port.h"
#include "net_multiset.h"

PNtalk::PN::SyncPort::SyncPort(Places places) : Transition(places){};
PNtalk::PN::SyncPort::SyncPort(const std::set<std::weak_ptr<Net::Transition>, transitions_compare> &update_transitions, std::weak_ptr<Net::Transition> parent) : Transition({}, parent) {
    _update_transitions = update_transitions;
};

bool PNtalk::PN::SyncPort::scheduler_execute() {
    update();
    return true;
}

bool PNtalk::PN::SyncPort::scheduler_check() {
    return true;
}

bool PNtalk::PN::SyncPort::match(const std::string &place_name, const MultiSet &edge_expr) {
    return Transition::match(place_name, edge_expr);
}
bool PNtalk::PN::SyncPort::pop(const std::string &place_name, const MultiSet &edge_expr) {
    return Transition::pop(place_name, edge_expr);
}
void PNtalk::PN::SyncPort::push(const std::string &place_name, const MultiSet &edge_expr) {
    Transition::push(place_name, edge_expr);
}
