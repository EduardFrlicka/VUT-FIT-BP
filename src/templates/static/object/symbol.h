#pragma once
#include "object_base.h"
#include "string.h"
#include <map>

namespace PNtalk {
class Symbol : public ObjectBase {
  public:
    class SymbolObj {};
    typedef ObjectBase super;
    static std::map<std::string, SymbolObj> symbol_table;
    std::map<std::string, SymbolObj>::iterator _it;

    Symbol();
    Symbol(const std::string &value);
    Symbol(const String &value);

    MessageTranslator<Symbol> message_translator;
    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    MessageResult _eq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _neq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult toString(ThisObj this_obj, MessageArguments arguments);

    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};

} // namespace PNtalk
