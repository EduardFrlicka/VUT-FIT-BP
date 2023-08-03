#include "symbol.h"
#include "object.h"

using namespace PNtalk;

std::map<std::string, Symbol::SymbolObj> PNtalk::Symbol::symbol_table = {};

PNtalk::Symbol::Symbol() {
    message_translator["_eq_"] = &Symbol::_eq_;
    message_translator["_eqi_"] = &Symbol::_eq_;
    message_translator["_neq_"] = &Symbol::_neq_;
    message_translator["_neqi_"] = &Symbol::_neq_;
    message_translator["asString"] = &Symbol::asString;
}

PNtalk::Symbol::Symbol(const std::string &value) : Symbol() {
    if (symbol_table.find(value) == symbol_table.end()) {
        symbol_table[value] = SymbolObj();
    }

    _it = symbol_table.find(value);
}

PNtalk::Symbol::Symbol(const String &value) : Symbol(value._value){};

MessageResult Symbol::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::Symbol::_eq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_it == arguments[0]->get<Symbol>()._it));
}

MessageResult PNtalk::Symbol::_neq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_it != arguments[0]->get<Symbol>()._it));
}

MessageResult PNtalk::Symbol::asString(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(String(_it->first));
}

MessageResult PNtalk::Symbol::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    std::cout << "Symbol does not understand message with selector: " << std::endl;
    return MessageResult();
}
