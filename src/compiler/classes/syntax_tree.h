#pragma once

#include "token.h"

namespace AbstractSyntaxTree {

class BaseNode {
  public:
    BaseNode(Token &);

    Token &token;
};

class ClassesNode : BaseNode {
  public:
    ClassesNode(Token &);
};

class ClassNode : BaseNode {
  public:
    ClassNode(Token &);
};

} // namespace AbstractSyntaxTree

namespace ast = AbstractSyntaxTree;
