#pragma once
#include "token.h"

namespace AbstractSyntaxTree {

class Base {
  public:
    TokenStackIterator begin;
    TokenStackIterator end;
    virtual void print(int indent = 0) const;

  protected:
    void print_indent(int) const;
};
} // namespace AbstractSyntaxTree

namespace ast = AbstractSyntaxTree;
