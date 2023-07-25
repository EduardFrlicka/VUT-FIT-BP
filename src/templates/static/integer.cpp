#include "integer.h"

using namespace PNtalk;

std::shared_ptr<Object> PNtalk::Integer::message(std::weak_ptr<Object> this_obj, const std::string &message_selector, const std::deque<Object> &arguments) {
    return std::shared_ptr<Object>();
}

PNtalk::Integer::Integer() : _value(0){};
PNtalk::Integer::Integer(int value) : _value(value){};