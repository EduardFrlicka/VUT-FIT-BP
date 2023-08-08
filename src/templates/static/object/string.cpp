#include "string.h"
#include "object.h"

// PNtalk::Object PNtalk::String::message(const std::string &message_selector, const std::deque<PNtalk::Object> &arguments) {
//     if (message_selector == "at")
//         return at(arguments);
//     return PNtalk::Object();
// }

using namespace PNtalk;

PNtalk::String::String() : super() {
    // message_translator["at_"] = &String::at_;
    message_translator["_eq_"] = &String::_eq_;
    message_translator["_neq_"] = &String::_neq_;
    message_translator["_lt_"] = &String::_lt_;
    message_translator["_gt_"] = &String::_gt_;
    message_translator["_gte_"] = &String::_gte_;
    message_translator["_lte_"] = &String::_lte_;
    message_translator["toString"] = &String::toString;
    message_translator["doesNotUnderstand_"] = &String::doesNotUnderstand_;
}

PNtalk::String::String(std::string value) : String() {
    _value = value;
}

MessageResult String::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::String::_eq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value == arguments[0]->get<String>()._value));
}

MessageResult PNtalk::String::_neq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value != arguments[0]->get<String>()._value));
}

MessageResult PNtalk::String::_lt_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value < arguments[0]->get<String>()._value));
}

MessageResult PNtalk::String::_gt_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value > arguments[0]->get<String>()._value));
}

MessageResult PNtalk::String::_gte_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value >= arguments[0]->get<String>()._value));
}

MessageResult PNtalk::String::_lte_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value <= arguments[0]->get<String>()._value));
}

MessageResult PNtalk::String::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}

MessageResult PNtalk::String::toString(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(String(_value));
}
