#include "nil.h"
#include "object.h"

using namespace PNtalk;

PNtalk::Nil::Nil() {
    message_translator["_eq_"] = &Nil::_eq_;
    message_translator["_eqi_"] = &Nil::_eq_;
    message_translator["_neq_"] = &Nil::_neq_;
    message_translator["_neqi_"] = &Nil::_neq_;
    message_translator["doesNotUnderstand_"] = &Nil::doesNotUnderstand_;
}

MessageResult Nil::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::Nil::_eq_(ThisObj this_obj, MessageArguments arguments) {
    if (arguments[0]->is_type<Nil>())
        return make_shared_obj(Bool(true));
    return make_shared_obj(Bool(false));
}

MessageResult PNtalk::Nil::_neq_(ThisObj this_obj, MessageArguments arguments) {
    if (arguments[0]->is_type<Nil>())
        return make_shared_obj(Bool(false));
    return make_shared_obj(Bool(true));
}

MessageResult PNtalk::Nil::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}
