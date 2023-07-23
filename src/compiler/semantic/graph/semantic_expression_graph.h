#include "identifier.h"
#include "semantic_graph_base.h"
#include <memory>
#include <variant>

namespace AbstractSemanticGraph {

class Expressions;
class Assigment;
class KeywordMessage;
class BinaryMessage;
class UnaryMessage;
class Literal;
class Variable;
class ClassRef;
class Bracket;
class CodeBlock;
class ConstArray;

typedef std::variant<Assigment, KeywordMessage, BinaryMessage, UnaryMessage, Literal, Variable, ClassRef, Bracket, Expressions, CodeBlock, ConstArray> ExprVariant;

class Expression : public Base {
  public:
    Expression();
    Expression(const Expressions &_val);
    Expression(const Assigment &_val);
    Expression(const KeywordMessage &_val);
    Expression(const BinaryMessage &_val);
    Expression(const UnaryMessage &_val);
    Expression(const Literal &_val);
    Expression(const Variable &_val);
    Expression(const ClassRef &_val);
    Expression(const Bracket &_val);
    Expression(const CodeBlock &_val);
    Expression(const ConstArray &_val);

    std::shared_ptr<ExprVariant> value;

    template <class T> T get();
    template <class T> bool is_type();
};

class Expressions : public Base {
  public:
    Expressions();
    Expressions(const std::deque<Expression> &_exprs);
    std::deque<Expression> exprs;
};

class Assigment : public Base {
  public:
    Identifier target;
    Expression value;
};

class KeywordMessage : public Base {
  public:
    Expression recv;
    Identifier selector;
    std::deque<Expression> arguments;
};

class BinaryMessage : public Base {
  public:
    Expression recv;
    TokenType selector;
    Expression argument;
};

class UnaryMessage : public Base {
  public:
    Expression recv;
    Identifier selector;
};

class Literal : public Base {
  public:
    Literal();
    Literal(TokenPayload);
    TokenPayload value;
};

class Variable : public Base {
  public:
    Variable();
    Variable(const Identifier &_id);
    Identifier id;
};

class ClassRef : public Base {
  public:
    ClassRef();
    ClassRef(const Identifier &_id);
    Identifier id;
};

class Bracket : public Base {
  public:
    Bracket();
    Bracket(const Expression &_expr);
    Expression expr;
};

class CodeBlock : public Base {
  public:
    std::deque<Identifier> arguments;
    std::deque<Identifier> temps;
    Expression expr;
};

class ConstArray : public Base {
  public:
    std::deque<Literal> elements;
};

template <class T> inline T Expression::get() {
    return std::get<T>(*value);
};

template <class T> inline bool Expression::is_type() {
    return std::holds_alternative<T>(*value);
};

} // namespace AbstractSemanticGraph
