#pragma once
#include "object_base.h"

namespace PNtalk {
class Nil : public ObjectBase {
  public:
    typedef ObjectBase super;

    Nil();

    MessageTranslator<Nil> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    MessageResult _eq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _neq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
