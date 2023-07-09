#pragma once
#include "deque"
#include "memory"
#include "syntax_tree_base.h"
#include "token.h"
#include "variant"

namespace AbstractSyntaxTree {

class ExpressionPair;
class CascadeUnary;
class CascadeBinary;
class CascadeKeyWord;
class ExpressionIdentifier;
class ExpressionValue;
class ExpressionUnary;
class ExpressionBinary;
class ExpressionKeyWord;
class Assgiment;

typedef std::variant<ExpressionPair, CascadeUnary, CascadeBinary, CascadeKeyWord, ExpressionIdentifier, ExpressionValue, ExpressionUnary, ExpressionBinary, ExpressionKeyWord, Assgiment> ExprVal;

class Expression : public Base {
  public:
    Expression();
    // Expression(const Expression &);
    Expression(const ExpressionPair &);
    Expression(const CascadeUnary &);
    Expression(const CascadeBinary &);
    Expression(const CascadeKeyWord &);
    Expression(const ExpressionIdentifier &);
    Expression(const ExpressionValue &);
    Expression(const ExpressionUnary &);
    Expression(const ExpressionBinary &);
    Expression(const ExpressionKeyWord &);
    Expression(const Assgiment &);

    std::shared_ptr<ExprVal> value;
    void print(int indent = 0);
};

class ExpressionPair : public Base {
  public:
    ExpressionPair(const Expression &, const Expression &);
    Expression first;
    Expression second;
    void print(int indent = 0);
};

class CascadeUnary : public Base {
  public:
    CascadeUnary(const Expression &, const Token &);
    Expression recv;
    Token message_selector;
    void print(int indent = 0);
};

class CascadeBinary : public Base {
  public:
    CascadeBinary(const Expression &, const Token &, const Expression &);
    Expression recv;
    Token message_selector;
    Expression argument;
    void print(int indent = 0);
};

class CascadeKeyWord : public Base {
  public:
    CascadeKeyWord(const Expression &, const std::deque<Token> &, const std::deque<Expression> &);
    Expression recv;
    std::deque<Token> selector;
    std::deque<Expression> arguments;
    void print(int indent = 0);
};

class ExpressionIdentifier : public Base {
  public:
    ExpressionIdentifier(const Token &);
    Token value;
    void print(int indent = 0);
};

class ExpressionValue : public Base {
  public:
    ExpressionValue(const Token &);
    Token value;
    void print(int indent = 0);
};

class ExpressionUnary : public Base {
  public:
    ExpressionUnary(const Expression &, const Token &);
    Expression recv;
    Token message_selector;
    void print(int indent = 0);
};

class ExpressionBinary : public Base {
  public:
    ExpressionBinary(const Expression &, const Token &, const Expression &);
    Expression recv;
    Token message_selector;
    Expression argument;
    void print(int indent = 0);
};

class ExpressionKeyWord : public Base {
  public:
    ExpressionKeyWord(const Expression &, const std::deque<Token> &, const std::deque<Expression> &);
    Expression recv;
    std::deque<Token> selector;
    std::deque<Expression> arguments;
    void print(int indent = 0);
};

class Assgiment : public Base {
  public:
    Assgiment(const Token &, const Expression &);
    Token target;
    Expression value;
    void print(int indent = 0);
};

} // namespace AbstractSyntaxTree
