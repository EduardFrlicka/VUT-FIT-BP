#include "net_place.h"

bool PN::PlaceTransaction::try_pop(int count, const Object &value) {
    return false;
}

bool PN::PlaceTransaction::try_pop(int count, std::shared_ptr<Object> &bind) {
    return false;
}
