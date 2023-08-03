#include "net_PN.h"
#include "scheduler.h"
#include <iostream>
#include <syncstream>

using namespace PNtalk;

PN::PN() : ObjectBase(), Net() {
    message_translator["doesNotUnderstand_"] = &PN::doesNotUnderstand_;
    message_translator["new"] = &PN::_new_;
}

MessageResult PN::_new_(ThisObj this_obj, MessageArguments arguments) {
    distribute_self(this_obj);
    scheduler.schedule(transitions);

    return this_obj;
};

MessageResult PN::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PN::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    std::osyncstream(std::cout) << "PN does not understand message with selector: " << std::endl;
    return MessageResult();
}