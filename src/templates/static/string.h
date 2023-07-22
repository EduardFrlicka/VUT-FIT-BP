#pragma once
#include "object_base.h"
#include <iostream>
#include <string>

namespace PN {

class String : public ObjectBase {
  public:
    typedef ObjectBase super;
    typedef String self;
    String();

    std::map<std::string, Object (String::*)(const std::deque<Object> &)> message_translator;

    Object message(const std::string &, const std::deque<Object> &);

    Object at(const std::deque<Object> &);
};

} // namespace PN
