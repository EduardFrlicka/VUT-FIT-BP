#include "net_multiset.h"
#include "boolean.h"
#include "object.h"

using namespace PNtalk;

PNtalk::MultiSetItem::MultiSetItem(){};
PNtalk::MultiSetItem::MultiSetItem(const std::shared_ptr<Object> &value) : _value(value){};
PNtalk::MultiSetItem::MultiSetItem(const MultiSetList &value) : _value(value){};

PNtalk::MultiSetPair::MultiSetPair(const std::shared_ptr<Object> &value) : _count(Integer(1)), _value(value){};
PNtalk::MultiSetPair::MultiSetPair(const std::shared_ptr<Object> &count, const std::shared_ptr<Object> &value) {
    if (!count)
        exit(1);
    _count = count->get<Integer>();
    _value = value;
};
PNtalk::MultiSetPair::MultiSetPair(const std::shared_ptr<Object> &count, const MultiSetList &value) {
    if (!count)
        exit(1);
    _count = count->get<Integer>();
    _value = value;
};

PNtalk::MultiSetList::MultiSetList(){};
PNtalk::MultiSetList::MultiSetList(const std::deque<MultiSetItem> &values) : _values(values){};
PNtalk::MultiSetList::MultiSetList(const std::deque<MultiSetItem> &values, const std::shared_ptr<Object> &tail) : _values(values), _tail(tail){};

PNtalk::MultiSet::MultiSet(){};
PNtalk::MultiSet::MultiSet(const std::deque<MultiSetPair> &pairs) {
    for (auto pair : pairs) {
        for (int i = 0; i < pair._count._value; i++)
            values.push_back(pair._value);
    }
};
PNtalk::MultiSet::MultiSet(const std::shared_ptr<Object> &object) {
    values.push_back(object);
};

bool PNtalk::MultiSetList::match(const PNtalk::MultiSetList &other) const {
    if (!_tail && !other._tail) {
        if (_values.size() != other._values.size())
            return false;

        auto left = _values.begin();
        auto right = other._values.begin();
        for (; left != _values.end(); left++, right++) {
            if (left->match(*right))
                return false;
        }
    }

    return true;
}

bool PNtalk::MultiSetItem::match(const PNtalk::MultiSetItem &other) const {
    if (std::holds_alternative<std::shared_ptr<PNtalk::Object>>(other._value) && std::holds_alternative<std::shared_ptr<PNtalk::Object>>(_value)) {
        auto &left = std::get<std::shared_ptr<PNtalk::Object>>(other._value);
        auto &right = std::get<std::shared_ptr<PNtalk::Object>>(_value);

        if (left->empty() && right->empty()) {
            return false;
        }
        if (left->empty()) {
            left->_value = right->_value;
            return true;
        }
        if (right->empty()) {
            right->_value = left->_value;
            return true;
        }
        return left->message("_eq_", {right})->get<Bool>()._value;
    }

    if (std::holds_alternative<MultiSetList>(other._value) && std::holds_alternative<std::shared_ptr<PNtalk::Object>>(_value)) {
        // auto &left = std::get<MultiSetList>(other._value);
        // auto &right = std::get<std::shared_ptr<PNtalk::Object>>(_value);
        return false;
    }

    if (std::holds_alternative<std::shared_ptr<PNtalk::Object>>(other._value) && std::holds_alternative<MultiSetList>(_value)) {
        // auto &left = std::get<std::shared_ptr<PNtalk::Object>>(other._value);
        // auto &right = std::get<MultiSetList>(_value);
        return false;
    }

    if (std::holds_alternative<MultiSetList>(other._value) && std::holds_alternative<MultiSetList>(_value)) {
        auto &left = std::get<MultiSetList>(other._value);
        auto &right = std::get<MultiSetList>(_value);
        return left.match(right);
    }

    return false;
}
