#pragma once
#include "basic_identifier.h"
#include "token.h"
#include <string>

class Identifier {
  public:
    Identifier();
    Identifier(const std::string &);
    Identifier(const BasicIdentifier &);

    BasicIdentifier id;
    bool defined;

    TokenStackIterator declaration_begin;
    TokenStackIterator declaration_end;

    TokenStackIterator definition_begin;
    TokenStackIterator definition_end;

    std::string toString() const;

    void declare(TokenStackIterator);
    void define(TokenStackIterator);
    void declare_define(TokenStackIterator);
  
    void declare(TokenStackIterator, TokenStackIterator);
    void define(TokenStackIterator, TokenStackIterator);
    void declare_define(TokenStackIterator, TokenStackIterator);

    

    Identifier operator+(const std::string &);
    Identifier operator+(const BasicIdentifier &);
    Identifier operator+(const Identifier &);
};