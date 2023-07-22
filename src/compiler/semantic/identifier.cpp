#include "identifier.h"

#define IDENTIFIER_DELIMITER "_"

Identifier::Identifier() : id(BasicIdentifier()), defined(false) {
}

Identifier::Identifier(const std::string &name) : id(name), defined(false) {
}
Identifier::Identifier(const BasicIdentifier &_id) : id(_id), defined(false) {
}

std::string Identifier::toString() const {
    return id.name;
}

void Identifier::declare(TokenStackIterator it) {
    declaration_begin = it;
    declaration_end = it;
}

void Identifier::define(TokenStackIterator it) {
    defined = true;
    definition_begin = it;
    definition_end = it;
}

void Identifier::declare_define(TokenStackIterator it) {
    declare(it);
    define(it);
}

void Identifier::declare(TokenStackIterator begin, TokenStackIterator end) {
    declaration_begin = begin;
    declaration_end = end;
}

void Identifier::define(TokenStackIterator begin, TokenStackIterator end) {
    defined = true;
    definition_begin = begin;
    definition_end = end;
}

void Identifier::declare_define(TokenStackIterator begin, TokenStackIterator end) {
    declare(begin, end);
    define(begin, end);
}

Identifier Identifier::operator+(const std::string &other) {
    if (id.name == other)
        return *this;

    return Identifier(id.name + IDENTIFIER_DELIMITER + other);
}

Identifier Identifier::operator+(const BasicIdentifier &other) {
    if (id.name == other.name)
        return *this;

    return Identifier(id.name + IDENTIFIER_DELIMITER + other.name);
}
Identifier Identifier::operator+(const Identifier &other) {
    if (id.name == other.id.name)
        return *this;

    return Identifier(id.name + IDENTIFIER_DELIMITER + other.id.name);
}
