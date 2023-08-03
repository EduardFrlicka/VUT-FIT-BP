#include "boolean.h"
#include "object.h"

using namespace PNtalk;

PNtalk::Bool::Bool() {
}

PNtalk::Bool::Bool(bool value) : _value(value) {
}

PNtalk::Bool::operator bool() const {
    return _value;
}

bool PNtalk::Bool::operator==(const PNtalk::Bool &other) const {
    return other._value == _value;
}
bool PNtalk::Bool::operator!=(const PNtalk::Bool &other) const {
    return other._value != _value;
}
bool PNtalk::Bool::operator!() const {
    return !_value;
}

MessageResult PNtalk::Bool::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::Bool::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}

MessageResult PNtalk::Bool::_eq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value == arguments.front()->get<Bool>()._value));
}

MessageResult PNtalk::Bool::_neq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value != arguments.front()->get<Bool>()._value));
}