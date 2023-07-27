#pragma once
#include "object_base.h"
#include <functional>

namespace PNtalk {
class CodeBlock : public ObjectBase {
  public:
    typedef ObjectBase super;

    CodeBlock(std::function<std::shared_ptr<Object>(MessageArguments)> function);

    MessageTranslator<CodeBlock> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);
    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
