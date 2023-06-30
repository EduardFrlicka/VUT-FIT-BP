#pragma once

#include "token.h"
#include <string>
#include <vector>

namespace AbstractSyntaxTree {

enum Types {
    typeIdentifier,
    typeSymbol,
    typeChar,
    typeString,
    typeNumber,
    typeArray,
};

typedef std::string Identifier;
typedef std::string Symbol;
typedef char Character;
typedef std::string String;

struct Number {
    std::string *base;
    std::string *decimal;
    int *radix;
    int *exponent;
};

struct Array;

struct Elem {
    union {
        Identifier *identifier;
        Symbol *symbol;
        Character *character;
        String *string;
        Number *number;
        Array *array;
    } elem;

    enum {
        elemIdentifier,
        elemSymbol,
        elemCharacter,
        elemString,
        elemNumber,
        elemArray,
    } type;
};

struct Array {
    std::vector<Elem *> elements;
};

struct ArrayConst {
    Array *array;
};

struct MultisetElem {
    enum {
        list,
    };
};
struct Multiset {};

struct Transition {};
struct Place {};
struct Net {};
struct ObjectNet {
    Net *net;
};
struct ClassHead {
    Token *token_name;
    Token *token_type;
    Identifier *name;
    Identifier *type;
};

struct Class {
    Token *token;
    ClassHead *head;
};

struct Classes {
    std::vector<Class *> classes;
};

void print_tree(Classes);
void print_tree(Class);

}; // namespace AbstractSyntaxTree

namespace ast = AbstractSyntaxTree;
