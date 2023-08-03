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
PNtalk::Object::Object(std::weak_ptr<Net::Transition> &&value) : _value(std::make_shared<ObjectVariant>(ObjectVariant(value))){};
/*?__generated__*/

void PNtalk::Object::reset() {
    _value = nullptr;
}

bool PNtalk::Object::empty() {
    return _value == nullptr;
}
