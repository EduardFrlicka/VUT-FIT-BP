#include "object.h"
#include <variant>

PN::Object PN::Object::message(const std::string &message_selector, const std::deque<Object> &arguments) {
    value.load().get();

    return Object();
}