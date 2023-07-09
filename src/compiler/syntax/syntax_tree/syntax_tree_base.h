#pragma once

namespace AbstractSyntaxTree {

class Base {
  public:
    virtual void print(int indent = 0);

  protected:
    void print_indent(int);
};
} // namespace AbstractSyntaxTree

namespace ast = AbstractSyntaxTree;
