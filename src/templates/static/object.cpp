#include "object.h"
#include <variant>

using namespace PNtalk;

PNtalk::Object::Object(){};
PNtalk::Object::Object(PNtalk::String &&value) : _value(std::make_shared<Variant>(Variant(value))){};
PNtalk::Object::Object(Bool &&value) : _value(std::make_shared<Variant>(Variant(value))){};

std::shared_ptr<Object> PNtalk::Object::message(const std::string &message_selector, const std::deque<std::shared_ptr<Object>> &arguments) {
    if (is_type<PNtalk::String>())
        return get<PNtalk::String>().message(weak_from_this(), message_selector, arguments);

    /*?__generated__*/
    std::cout << "Object failed to match class" << std::endl;
    exit(1);
}
