#pragma once

#include "object.h"
#include <deque>
#include <memory>

namespace PNtalk {

class MultiSetItem;

class MultiSetList {
    std::deque<MultiSetItem> values;
};

class MultiSetItem {
  public:
    Integer _count;
    std::shared_ptr<Object> _value;
    MultiSetItem(std::shared_ptr<Object> value);
    MultiSetItem(Integer count, std::shared_ptr<Object> value);
};

typedef std::deque<MultiSetItem> MultiSet;
class PN::Place {
    std::deque<std::shared_ptr<Object>> values;

    virtual void update();
};

} // namespace PNtalk
