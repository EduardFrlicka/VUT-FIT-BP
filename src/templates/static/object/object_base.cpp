#include "object_base.h"
#include "object.h"
#include <iostream>
#include <syncstream>

using namespace PNtalk;

// std::atomic<long> id_counter = 0;

ObjectBase::ObjectBase() {
    // id = id_counter++;

    message_translator["_eqi_"] = &ObjectBase::_eqi_;
    message_translator["_neqi_"] = &ObjectBase::_neqi_;
}

MessageResult ObjectBase::_eqi_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(this_obj->_value == arguments.front()->_value));
}

MessageResult ObjectBase::_neqi_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(this_obj->_value != arguments.front()->_value));
}

MessageResult ObjectBase::message(ThisObj this_obj, const std::string &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        std::deque<std::shared_ptr<Object>> message = {make_shared_obj(String(message_selector))};
        message.insert(message.end(), arguments.begin(), arguments.end());
        std::osyncstream(std::cout) << "Base not understand: \"" << message_selector << "\"" << std::endl;
        this_obj->message("doesNotUnderstand_", {message});
        exit(1);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}
