#include "boolean.h"

PNtalk::Bool::Bool() {
}

PNtalk::Bool::Bool(bool value): _value(value) {
}

PNtalk::Bool::operator bool() const {
    return _value;
}

bool PNtalk::Bool::operator==(const PNtalk::Bool &other) const {
    return other._value == _value;
}
bool PNtalk::Bool::operator!=(const PNtalk::Bool &other) const {
    return other._value != _value;
}
bool PNtalk::Bool::operator!() const {
    return !_value;
}
