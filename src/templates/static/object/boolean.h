#pragma once

#include "object_base.h"

namespace PNtalk {
class Bool : public ObjectBase {
  public:
    typedef ObjectBase super;
    bool _value;
    Bool();
    Bool(bool value);
    explicit operator bool() const;
    bool operator==(const Bool &) const;
    bool operator!=(const Bool &) const;
    bool operator!() const;

    MessageResult message(ThisObj this_obj, const MessageSelector &message_selector, MessageArguments arguments);

    // virtual Object message(const std::string &, const std::deque<Object> &);
    // virtual Object _eq_(const std::deque<Object> &);
    // virtual Object _neq_(const std::deque<Object> &);
    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};
} // namespace PNtalk
