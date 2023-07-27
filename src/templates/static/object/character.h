#pragma once
#include "object_base.h"
#include <iostream>
#include <string>

namespace PNtalk {

class Character : public ObjectBase {
  public:
    typedef ObjectBase super;

    Character();
    Character(char value);

    MessageTranslator<Character> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
