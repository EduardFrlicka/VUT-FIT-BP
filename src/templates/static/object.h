#pragma once
#include "integer.h"
#include "string.h"
#include "boolean.h"
#include <atomic>
#include <iostream>
#include <memory>
#include <variant>

#include "net_PN.h"
#include "net_place.h"
#include "net_transition.h"

namespace PNtalk {
class Object : public std::enable_shared_from_this<Object> {
    typedef std::variant<String, Bool /*?, __generated__*/> Variant;

  public:
    std::shared_ptr<Variant> _value;

    Object();
    Object(String &&value);
    Object(Bool &&value);

    std::shared_ptr<Object> message(const std::string &message_selector, const std::deque<std::shared_ptr<Object>> &arguments);
    template <class T> T &get();
    template <class T> bool is_type() const;
};

template <class T> inline T &Object::get() {
    if (!std::holds_alternative<T>(*_value)) {
        std::cerr << "Semantic error" << std::endl;
        /* TODO SEMANTIC ERROR HANDLE */
        exit(1);
    }
    return std::get<T>(*_value);
}

template <class T> inline bool Object::is_type() const {
    if (!_value)
        return false;
    return std::holds_alternative<T>(*_value);
}

} // namespace PNtalk