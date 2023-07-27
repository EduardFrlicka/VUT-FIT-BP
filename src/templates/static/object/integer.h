#pragma once
#include "object_base.h"

namespace PNtalk {
class Integer : public ObjectBase {
  public:
    typedef ObjectBase super;
    int _value;

    Integer();
    Integer(int value);

    MessageTranslator<Integer> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    MessageResult even(ThisObj this_obj, MessageArguments arguments);
    MessageResult odd(ThisObj this_obj, MessageArguments arguments);

    MessageResult _add_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _sub_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _mul_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _div_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _idiv_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _mod_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _eq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _neq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _lt_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _gt_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _gte_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _lte_(ThisObj this_obj, MessageArguments arguments);

    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
