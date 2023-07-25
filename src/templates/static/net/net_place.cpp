#include "net_place.h"

void PNtalk::PN::Place::update() {
}

PNtalk::MultiSetItem::MultiSetItem(std::shared_ptr<Object> value) : _value(value){};
PNtalk::MultiSetItem::MultiSetItem(Integer count, std::shared_ptr<Object> value) : _count(count), _value(value){};
