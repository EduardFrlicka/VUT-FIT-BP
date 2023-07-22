#include "boolean.h"

PN::Bool::operator bool() const {
    return value;
}

bool PN::Bool::operator==(const PN::Bool &other) const {
    return other.value == value;
}
bool PN::Bool::operator!=(const PN::Bool &other) const {
    return other.value != value;
}
bool PN::Bool::operator!() const {
    return !value;
}
