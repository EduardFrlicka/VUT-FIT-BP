#pragma once
#include "object_base.h"
#include <iostream>
#include <string>

namespace PNtalk {

class String : public ObjectBase {
  public:
    typedef ObjectBase super;
    typedef String self;

    std::string _value;
    String();
    String(std::string value);

    MessageTranslator<String> message_translator;

    virtual std::shared_ptr<Object> message(std::weak_ptr<Object> this_obj, const std::string &message_selector, MessageArguments arguments);

    std::shared_ptr<Object> at(std::weak_ptr<Object> this_obj, MessageArguments arguments);
};

} // namespace PNtalk
