#include "integer.h"
#include "boolean.h"
#include "object.h"

using namespace PNtalk;

MessageResult Integer::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult Integer::even(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value % 2 == 0));
}

MessageResult Integer::odd(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value % 2 == 1));
}

MessageResult Integer::_add_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value + arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_sub_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value - arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_mul_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value * arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_div_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value / arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_idiv_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value / arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_mod_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value % arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_eq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value == arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_neq_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value != arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_lt_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value < arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_gt_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value > arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_gte_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value >= arguments.front()->get<Integer>()._value));
}

MessageResult Integer::_lte_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value <= arguments.front()->get<Integer>()._value));
}

MessageResult Integer::toString(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(String(std::to_string(_value)));
}

MessageResult Integer::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}

MessageResult PNtalk::Integer::allMask_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool((_value & arguments.front()->get<Integer>()._value) == arguments.front()->get<Integer>()._value));
};
MessageResult PNtalk::Integer::anyMask_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_value & arguments.front()->get<Integer>()._value));
};
MessageResult PNtalk::Integer::bitAt_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer((_value >> (arguments.front()->get<Integer>()._value - 1)) & 1));
};
MessageResult PNtalk::Integer::bitAt_put_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer((_value & (~1 << ((arguments[0]->get<Integer>()._value) - 1)) | (1 & arguments[1]->get<Integer>()._value) << (arguments[0]->get<Integer>()._value) - 1)));
};
MessageResult PNtalk::Integer::bitClear_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value & ~arguments.front()->get<Integer>()._value));
};
MessageResult PNtalk::Integer::bitInvert(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(~_value));
};
MessageResult PNtalk::Integer::clearBit_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value & (~1 << ((arguments[0]->get<Integer>()._value) - 1))));
};
MessageResult PNtalk::Integer::setBit(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_value | (1 << ((arguments[0]->get<Integer>()._value) - 1))));
};

Integer::Integer() : ObjectBase() {
    message_translator["even"] = &Integer::even;
    message_translator["odd"] = &Integer::odd;
    message_translator["_add_"] = &Integer::_add_;
    message_translator["_sub_"] = &Integer::_sub_;
    message_translator["_mul_"] = &Integer::_mul_;
    message_translator["_div_"] = &Integer::_div_;
    message_translator["_idiv_"] = &Integer::_idiv_;
    message_translator["_mod_"] = &Integer::_mod_;
    message_translator["_eq_"] = &Integer::_eq_;
    message_translator["_neq_"] = &Integer::_neq_;
    message_translator["_lt_"] = &Integer::_lt_;
    message_translator["_gt_"] = &Integer::_gt_;
    message_translator["_gte_"] = &Integer::_gte_;
    message_translator["_lte_"] = &Integer::_lte_;

    message_translator["allMask_"] = &Integer::allMask_;
    message_translator["anyMask_"] = &Integer::anyMask_;
    message_translator["bitAt_"] = &Integer::bitAt_;
    message_translator["bitAt_put_"] = &Integer::bitAt_put_;
    message_translator["bitClear_"] = &Integer::bitClear_;
    message_translator["bitInvert"] = &Integer::bitInvert;
    message_translator["clearBit_"] = &Integer::clearBit_;
    message_translator["setBit"] = &Integer::setBit;

    message_translator["toString"] = &Integer::toString;
    message_translator["doesNotUnderstand_"] = &Integer::doesNotUnderstand_;
};
Integer::Integer(int value) : Integer() {
    _value = value;
};