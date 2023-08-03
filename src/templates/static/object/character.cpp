#include "character.h"
#include "object.h"

using namespace PNtalk;

PNtalk::Character::Character() {
    message_translator["_eq_"] = &Character::_eq_;
    message_translator["_neq_"] = &Character::_neq_;
}

PNtalk::Character::Character(char value) : Character() {
    _value = value;
}

MessageResult PNtalk::Character::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::Character::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}

MessageResult PNtalk::Character::_eq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value == arguments.front()->get<Character>()._value));
}

MessageResult PNtalk::Character::_neq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value != arguments.front()->get<Character>()._value));
}
