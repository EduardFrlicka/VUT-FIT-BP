#include "object_base.h"
#include "object.h"
#include <iostream>

using namespace PNtalk;

// std::atomic<long> id_counter = 0;

ObjectBase::ObjectBase() {
    // id = id_counter++;

    message_translator["_eq_identity_"] = &ObjectBase::_eq_identity_;
    message_translator["_neq_identity_"] = &ObjectBase::_neq_identity_;
}

std::shared_ptr<Object> PNtalk::ObjectBase::_eq_identity_(std::weak_ptr<Object> this_obj, MessageArguments arguments) {
    std::cout << "base_obj" << std::endl;
    return std::make_shared<Object>(Object(Bool(this_obj.lock()->_value == arguments.front()->_value)));
}

std::shared_ptr<Object> PNtalk::ObjectBase::_neq_identity_(std::weak_ptr<Object> this_obj, MessageArguments arguments) {
    return std::make_shared<Object>(Object(Bool(this_obj.lock()->_value != arguments.front()->_value)));
}

std::shared_ptr<Object> ObjectBase::message(std::weak_ptr<Object> this_obj, const std::string &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        std::cout << "FAILED " << message_selector << std::endl;
        exit(1);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}
