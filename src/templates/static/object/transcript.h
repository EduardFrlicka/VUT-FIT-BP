#pragma once
#include "object_base.h"

namespace PNtalk {
class Transcript : public ObjectBase {
  public:
    typedef ObjectBase super;

    Transcript();

    MessageTranslator<Transcript> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    MessageResult cr(ThisObj this_obj, MessageArguments arguments);
    MessageResult show_(ThisObj this_obj, MessageArguments arguments);
    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
