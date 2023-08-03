#pragma once
#include "net_net.h"
#include "object_base.h"

namespace PNtalk {

class PN : public ObjectBase, public Net {
  public:
    typedef ObjectBase super;

    class Method;
    class SyncPort;
    PN();
    MessageTranslator<PN> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);
    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _new_(ThisObj this_obj, MessageArguments arguments);
};
} // namespace PNtalk
