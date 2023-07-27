#include "character.h"

using namespace PNtalk;


PNtalk::Character::Character() {
}

PNtalk::Character::Character(char value) {
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
