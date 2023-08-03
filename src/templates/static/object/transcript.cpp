#include "transcript.h"
#include "object.h"
#include <iostream>
#include <syncstream>

using namespace PNtalk;

PNtalk::Transcript::Transcript() {
    message_translator["cr"] = &Transcript::cr;
    message_translator["show_"] = &Transcript::show_;
    message_translator["doesNotUnderstand_"] = &Transcript::doesNotUnderstand_;
}

MessageResult Transcript::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::Transcript::cr(ThisObj this_obj, MessageArguments arguments) {
    std::cout << std::endl;
    return this_obj;
}

MessageResult PNtalk::Transcript::show_(ThisObj this_obj, MessageArguments arguments) {
    std::cout << arguments[0]->message("toString", {})->get<String>()._value << std::endl;
    return this_obj;
}

MessageResult PNtalk::Transcript::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}
