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
class Bracket;
class CodeBlock;
class ConstArray;

typedef std::variant<ExpressionPair, CascadeUnary, CascadeBinary, CascadeKeyWord, ExpressionIdentifier, ExpressionValue, ExpressionUnary, ExpressionBinary, ExpressionKeyWord, Assgiment, Bracket,
                     CodeBlock, ConstArray>
    ExprVal;

class Expression : public Base {
  public:
    Expression();
    // Expression(const Expression &);
    Expression(const ExpressionPair &, TokenStackIterator, TokenStackIterator);
    Expression(const CascadeUnary &, TokenStackIterator, TokenStackIterator);
    Expression(const CascadeBinary &, TokenStackIterator, TokenStackIterator);
    Expression(const CascadeKeyWord &, TokenStackIterator, TokenStackIterator);
    Expression(const ExpressionIdentifier &, TokenStackIterator);
    Expression(const ExpressionValue &, TokenStackIterator);
    Expression(const ExpressionUnary &, TokenStackIterator, TokenStackIterator);
    Expression(const ExpressionBinary &, TokenStackIterator, TokenStackIterator);
    Expression(const ExpressionKeyWord &, TokenStackIterator, TokenStackIterator);
    Expression(const Assgiment &, TokenStackIterator, TokenStackIterator);
    Expression(const Bracket &, TokenStackIterator, TokenStackIterator);
    Expression(const CodeBlock &, TokenStackIterator, TokenStackIterator);
    Expression(const ConstArray &, TokenStackIterator, TokenStackIterator);

    std::shared_ptr<ExprVal> value;
    bool isprimary() const;
    bool issecundary() const;
    bool iscascade() const;
    template <class T> T get() const;
    template <class T> bool is_type() const;

    void print(int indent = 0) const;
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

class Bracket : public Base {
  public:
    Bracket(const Expression &);
    Expression expr;
    void print(int indent = 0);
};

class CodeBlock : public Base {
  public:
    CodeBlock(const std::deque<Token> &, const std::deque<Token> &, const Expression &);

    std::deque<Token> arguments;
    std::deque<Token> temps;
    Expression expr;

    void print(int indent = 0);
};

class ConstArray : public Base {
  public:
    ConstArray(const std::deque<Token> &);

    std::deque<Token> elements;
    void print(int indent = 0);
};

template <class T> inline T Expression::get() const {
    return std::get<T>(*value);
};

template <class T> inline bool Expression::is_type() const {
    return std::holds_alternative<T>(*value);
};

} // namespace AbstractSyntaxTree
