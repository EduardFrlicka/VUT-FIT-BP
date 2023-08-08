#pragma once
#include "object_base.h"
#include <iostream>
#include <string>

namespace PNtalk {

class String : public ObjectBase {
  public:
    typedef ObjectBase super;
    typedef String self;

    std::string _value;
    String();
    String(std::string value);

    MessageTranslator<String> message_translator;

    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    MessageResult _eq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _neq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _lt_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _gt_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _gte_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _lte_(ThisObj this_obj, MessageArguments arguments);

    MessageResult toString(ThisObj this_obj, MessageArguments arguments);

    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
