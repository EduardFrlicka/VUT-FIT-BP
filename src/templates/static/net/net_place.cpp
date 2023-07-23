#include "net_place.h"

PN::PlaceTransaction::PlaceTransaction(Place &_place) : place(_place), it(place.values.begin()) {
}

bool PN::PlaceTransaction::try_pop(const Object &value, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        if (value.message("!=", {**it}))
            return false;
        it++;
    }
    return true;
}

bool PN::PlaceTransaction::try_pop(std::shared_ptr<Object> &bind, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        if (!bind) {
            bind = *it;
        }
        if (bind->message("!=", {**it}))
            return false;
        it++;
    }
    return true;
}
bool PN::PlaceTransaction::pop(const Object &value, unsigned int count) {

    return false;
}

bool PN::PlaceTransaction::pop(std::shared_ptr<Object> &bind, unsigned int count) {
    bind = std::make_shared(it);
    return false;
}

bool PN::PlaceTransaction::match(const Object &value, unsigned int count) {
    return false;
}
bool PN::PlaceTransaction::match(std::shared_ptr<Object> &bind, unsigned int count) {
    return false;
}
bool PN::PlaceTransaction::push(const Object &value, unsigned int count) {
    return false;
}
bool PN::PlaceTransaction::push(std::shared_ptr<Object> &bind, unsigned int count) {
    return false;
}
