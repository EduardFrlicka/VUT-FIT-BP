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

    MessageResult _eq_(ThisObj this_obj, MessageArguments arguments);
    MessageResult _neq_(ThisObj this_obj, MessageArguments arguments);

    MessageResult doesNotUnderstand_(ThisObj this_obj, MessageArguments arguments);
};
} // namespace PNtalk
