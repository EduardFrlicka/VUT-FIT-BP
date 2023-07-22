#include "object_base.h"
#include "object.h"
#include <iostream>

std::atomic<long> PN::id_counter = 0;

PN::ObjectBase::ObjectBase() {
    id = PN::id_counter++;

    message_translator["_eq_identity_"] = &ObjectBase::_eq_identity_;
    message_translator["_neq_identity_"] = &ObjectBase::_neq_identity_;
}

PN::Object PN::ObjectBase::message(const std::string &message_selector, const std::deque<PN::Object> &arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        std::cout << "FAILED " << message_selector << std::endl;
        return Object();
    }

    return (this->*(message_translator[message_selector]))(arguments);
}

PN::Object PN::ObjectBase::_eq_identity_(const std::deque<PN::Object> &) {
    return Object();
}

PN::Object PN::ObjectBase::_neq_identity_(const std::deque<PN::Object> &) {
    return Object();
}
