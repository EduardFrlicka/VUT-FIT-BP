#pragma once

#include "object_base.h"

namespace PNtalk {
class Bool : public ObjectBase {
  public:
    bool _value;
    Bool();
    Bool(bool value);
    explicit operator bool() const;
    bool operator==(const Bool &) const;
    bool operator!=(const Bool &) const;
    bool operator!() const;

    // virtual Object message(const std::string &, const std::deque<Object> &);
    // virtual Object _eq_(const std::deque<Object> &);
    // virtual Object _neq_(const std::deque<Object> &);
};
} // namespace PNtalk
