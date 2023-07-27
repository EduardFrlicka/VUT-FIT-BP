#include "net_place.h"
#include "object.h"

PNtalk::MultiSetItem::MultiSetItem(const std::shared_ptr<Object> &value) : _count(1), _value(value){};
PNtalk::MultiSetItem::MultiSetItem(const Integer &count, const std::shared_ptr<Object> &value) : _count(count), _value(value){};

bool PNtalk::PN::Place::match(std::weak_ptr<PN::Transition> trans, const MultiSet &edge_expr) {
    update_transitions.insert(trans);

    auto it = place.values.begin();
    for (auto &item : edge_expr) {
        for (int i = 0; i < item._count._value; i++) {
            if (it == place.values.end())
                return false;

            if (item._value->empty()) {
                *item._value = *it;
                continue;
            }

            if (it->message("_neq_", {item._value})->get<Bool>())
                return false;
        }
    }
    return true;
}

bool PNtalk::PN::Place::pop(std::weak_ptr<PN::Transition> trans, const MultiSet &edge_expr) {
    update_transitions.insert(trans);

    for (auto &item : edge_expr) {
        for (int i = 0; i < item._count._value; i++) {
            if (place.values.empty())
                return false;

            if (item._value->empty()) {
                *item._value = place.values.front();
                continue;
            }

            if (place.values.front().message("_neq_", {item._value})->get<Bool>())
                return false;

            place.values.pop_front();
        }
    }

    update();
    return true;
}

void PNtalk::PN::Place::push(const MultiSet &edge_expr) {

    update();
}

void PNtalk::PN::Place::update() {
    std::deque<std::weak_ptr<PN::Transition>> expired;
    std::set<std::string> scheduled;

    for (auto trans : update_transitions) {
        auto locked = trans.lock();

        if (trans.expired()) {
            expired.push_back(trans);
            continue;
        }

        if (scheduled.find(locked->name()) == scheduled.end())
            scheduled.insert(locked->name());

        schedule(locked);
    }

    for (auto trans : expired)
        update_transitions.erase(trans);
}
