#include "token.h"

void TokenPayloadSymbol::append(int c) {
    value += c;
}
std::string TokenPayloadSymbol::toString() const {
    return value;
}
void TokenPayloadString::append(int c) {
    value += c;
}
std::string TokenPayloadString::toString() const {
    return value;
}
void TokenPayloadCharacter::set(int c) {
    value = c;
}
std::string TokenPayloadCharacter::toString() const {
    return std::string(1, value);
}
