#pragma once
#include "net_PN.h"
#include "net_place.h"
#include "net_transition.h"
#include "object_variant.h"
#include <atomic>
#include <iostream>
#include <memory>
#include <syncstream>

namespace PNtalk {
class Object : public std::enable_shared_from_this<Object> {

  public:
    std::shared_ptr<ObjectVariant> _value;

    Object();
    Object(Bool &&value);
    Object(Integer &&value);
    Object(Character &&value);
    Object(String &&value);
    Object(Symbol &&value);
    Object(Array &&value);
    Object(CodeBlock &&value);
    Object(Transcript &&value);
    Object(std::weak_ptr<Net::Transition> &&value);
    /*?__generated__*/

    MessageResult message(const MessageSelector &message_selector, MessageArguments arguments);
    bool empty();
    void reset();
    template <class T> T &get();
    template <class T> bool is_type() const;
};

template <class T> inline T &Object::get() {
    if (!_value) {
        std::osyncstream(std::cerr) << "Semantic error: get on empty object" << std::endl;
        /* TODO SEMANTIC ERROR HANDLE */
        std::this_thread::sleep_for(std::chrono::seconds(2));

        throw std::invalid_argument("Semantic error: get on empty object");
    }
    if (!std::holds_alternative<T>(*_value)) {
        std::osyncstream(std::cerr) << "Semantic error: get wrong type " << typeid(T).name() << " and " << typeid(*_value).name() << std::endl;
        /* TODO SEMANTIC ERROR HANDLE */
        std::this_thread::sleep_for(std::chrono::seconds(2));
        throw std::invalid_argument("Semantic error: get wrong type");
    }
    return std::get<T>(*_value);
}

template <class T> inline bool Object::is_type() const {
    if (!_value)
        return false;
    return std::holds_alternative<T>(*_value);
}

} // namespace PNtalk