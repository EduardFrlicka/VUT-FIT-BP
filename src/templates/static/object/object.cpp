#include "object.h"
#include <variant>

using namespace PNtalk;

PNtalk::Object::Object() {
}
PNtalk::Object::Object(Bool &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
PNtalk::Object::Object(Integer &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
PNtalk::Object::Object(Character &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
PNtalk::Object::Object(String &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
PNtalk::Object::Object(Symbol &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
PNtalk::Object::Object(Array &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
PNtalk::Object::Object(CodeBlock &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
PNtalk::Object::Object(Transcript &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};

MessageResult PNtalk::Object::message(const MessageSelector &message_selector, MessageArguments arguments) {
    if (is_type<PNtalk::String>())
        return get<PNtalk::String>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Bool>())
        return get<PNtalk::Bool>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Integer>())
        return get<PNtalk::Integer>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Character>())
        return get<PNtalk::Character>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::String>())
        return get<PNtalk::String>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Symbol>())
        return get<PNtalk::Symbol>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Array>())
        return get<PNtalk::Array>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::CodeBlock>())
        return get<PNtalk::CodeBlock>().message(weak_from_this(), message_selector, arguments);
    if (is_type<PNtalk::Transcript>())
        return get<PNtalk::Transcript>().message(weak_from_this(), message_selector, arguments);
    /*?__generated__*/

    std::cout << "Object failed to match class" << std::endl;
    exit(1);
}

void PNtalk::Object::reset() {
    _value = nullptr;
}

bool PNtalk::Object::empty() {
    return _value == nullptr;
}
