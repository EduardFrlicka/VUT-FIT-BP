#pragma once
#include "number.h"
#include "string.h"
#include <atomic>
#include <iostream>
#include <memory>
#include <variant>

namespace PN {
class Object : public std::enable_shared_from_this<Object> {
    std::atomic<std::shared_ptr<std::variant<Number>>> value;

  public:
    virtual Object message(const std::string &, const std::deque<Object> &);
    template <class T> T get();
};

template <class T> inline T Object::get() {
    if (!std::holds_alternative<T>(value)) {
        std::cerr << "Semantic error" << std::endl;
        /* TODO SEMANTIC ERROR HANDLE */
        exit(1);
    }
    return std::get<T>(value);
}

} // namespace PN