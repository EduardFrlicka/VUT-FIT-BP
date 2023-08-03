#pragma once
#include "boolean.h"
#include "integer.h"
#include "object_base.h"
#include <deque>
#include <memory>
#include <variant>

namespace PNtalk {
class MultiSetItem;

class MultiSetList {
  public:
    std::deque<MultiSetItem> _values;
    std::shared_ptr<Object> _tail;

    MultiSetList();
    MultiSetList(const std::deque<MultiSetItem> &values);
    MultiSetList(const std::deque<MultiSetItem> &values, const std::shared_ptr<Object> &tail);
    bool match(const MultiSetList &other) const;
};

class MultiSetItem {
  public:
    std::variant<MultiSetList, std::shared_ptr<Object>> _value;

    MultiSetItem();
    MultiSetItem(const MultiSetList &value);
    MultiSetItem(const std::shared_ptr<Object> &value);

    bool match(const MultiSetItem &other) const;
};

class MultiSetPair {
  public:
    Integer _count;
    MultiSetItem _value;
    MultiSetPair(const std::shared_ptr<Object> &value);
    MultiSetPair(const std::shared_ptr<Object> &count, const std::shared_ptr<Object> &value);
    MultiSetPair(const std::shared_ptr<Object> &count, const MultiSetList &value);
};

class MultiSet {
  public:
    std::deque<MultiSetItem> values;

    MultiSet();
    MultiSet(const std::deque<MultiSetPair> &pairs);
    MultiSet(const std::shared_ptr<Object> &object);
};
} // namespace PNtalk