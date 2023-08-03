#include "code_block.h"

using namespace PNtalk;

MessageResult PNtalk::CodeBlock::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::CodeBlock::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}

CodeBlock::CodeBlock(std::function<std::shared_ptr<Object>(ThisObj, MessageArguments)> function) {
}
