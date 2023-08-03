#include "array.h"
#include "integer.h"
#include "object.h"
using namespace PNtalk;

MessageResult PNtalk::Array::message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments) {
    if (message_translator.find(message_selector) == message_translator.end()) {
        return super::message(this_obj, message_selector, arguments);
    }

    return (this->*(message_translator[message_selector]))(this_obj, arguments);
}

MessageResult PNtalk::Array::doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}

PNtalk::Array::Array() : ObjectBase() {
    message_translator["new_"] = &Array::new_;
    message_translator["with_"] = &Array::with_;
    message_translator["with_with_"] = &Array::with_with_;
    message_translator["with_with_with_"] = &Array::with_with_with_;
    message_translator["with_with_with_with_"] = &Array::with_with_with_with_;
    message_translator["with_with_with_with_with_"] = &Array::with_with_with_with_with_;
    message_translator["with_with_with_with_with_with_"] = &Array::with_with_with_with_with_with_;
    message_translator["withAll_"] = &Array::withAll_;

    message_translator["isEmpty"] = &Array::isEmpty;
    message_translator["size"] = &Array::size;
    message_translator["at_"] = &Array::at_;
    message_translator["at_put_"] = &Array::at_put_;
    message_translator["add_"] = &Array::add_;
    message_translator["addAll_"] = &Array::addAll_;
    message_translator["remove_"] = &Array::remove_;
    message_translator["removeAll_"] = &Array::removeAll_;
}

PNtalk::Array::Array(const std::deque<std::shared_ptr<Object>> &values) : Array() {
    _values = values;
}

MessageResult Array::new_(ThisObj this_obj, MessageArguments arguments) {
    _values.resize(arguments[0]->get<Integer>()._value);
    return this_obj;
};

MessageResult Array::with_(ThisObj this_obj, MessageArguments arguments) {
    return withAll_(this_obj, arguments);
}
MessageResult Array::with_with_(ThisObj this_obj, MessageArguments arguments) {
    return withAll_(this_obj, arguments);
}
MessageResult Array::with_with_with_(ThisObj this_obj, MessageArguments arguments) {
    return withAll_(this_obj, arguments);
}
MessageResult Array::with_with_with_with_(ThisObj this_obj, MessageArguments arguments) {
    return withAll_(this_obj, arguments);
}
MessageResult Array::with_with_with_with_with_(ThisObj this_obj, MessageArguments arguments) {
    return withAll_(this_obj, arguments);
}
MessageResult Array::with_with_with_with_with_with_(ThisObj this_obj, MessageArguments arguments) {
    return withAll_(this_obj, arguments);
}
MessageResult Array::withAll_(ThisObj this_obj, MessageArguments arguments) {
    for (auto i : arguments) {
        if (i->is_type<std::weak_ptr<Net::Transition>>())
            continue;
        _values.push_back(i);
    }
    return this_obj;
}

MessageResult Array::isEmpty(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Bool(_values.empty()));
}
MessageResult Array::size(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj(Integer(_values.size()));
}
MessageResult Array::at_(ThisObj this_obj, MessageArguments arguments) {
    return _values[arguments[0]->get<Integer>()._value];
}
MessageResult Array::at_put_(ThisObj this_obj, MessageArguments arguments) {
    _values[arguments[0]->get<Integer>()._value] = arguments[1];
    return this_obj;
}
MessageResult Array::add_(ThisObj this_obj, MessageArguments arguments) {
    _values.push_back(arguments[0]);
    return this_obj;
}
MessageResult Array::addAll_(ThisObj this_obj, MessageArguments arguments) {
    for (auto i : arguments[0]->get<Array>()._values) {
        _values.push_back(i);
    }
    return this_obj;
}
MessageResult Array::remove_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj();
}
MessageResult Array::removeAll_(ThisObj this_obj, MessageArguments arguments) {
    return make_shared_obj();
}

MessageResult PNtalk::Array::do_(ThisObj this_obj, MessageArguments arguments) {
    return MessageResult();
}
