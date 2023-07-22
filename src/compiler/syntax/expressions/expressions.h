#pragma once

#include "expressions_tree.h"
#include "token.h"
#include <variant>
#include <vector>

#define TABLE_SIZE 25

enum class ExprType;
enum class Precedence;

ExprType from_token(const Token &);

class ExpressionElem {
  public:
    ExpressionElem(ExprType);
    ExpressionElem(const Token &);
    ExpressionElem(const ast::Expression &);
    ExprType type;
    std::variant<Token, ast::Expression, std::monostate> value;
};

class PrecedenceTable {
  public:
    PrecedenceTable(const std::vector<std::vector<std::vector<Precedence>>> &);
    PrecedenceTable(const std::vector<std::vector<char>> &);
    PrecedenceTable();

    std::vector<std::vector<std::vector<Precedence>>> table;

    Precedence get(const ExpressionElem &, const Token &, const Token &);
    Precedence get(ExprType, ExprType, ExprType);
};

class ExpressionStack : private std::vector<ExpressionElem> {
    typedef std::vector<ExpressionElem> super;

  public:
    void print();
    ExpressionStack();
    void reset();
    const ExpressionElem &top();
    ExpressionElem &top_elem();
    bool match_top(const std::vector<ExprType> &);
    bool try_match_top(const std::vector<ExprType> &);
    template <class T> T pop();
    void pop();
    void push(const Token &);
    void push(const ast::Expression &);
    void push_stop();
};

class ExpressionSyntaxAnalyzer {
  private:
    PrecedenceTable table;
    ExpressionStack stack;
    TokenStackIterator &tokenStack;
    int reduce();

    void reduce_expression_concat();
    void reduce_expression_end();
    void reduce_unary_cascade();
    void reduce_binary_cascade();
    void reduce_keyword_cascade();
    void reduce_id();
    void reduce_lit();
    void reduce_bracket();
    void reduce_unary_message();
    void reduce_binary_message();
    void reduce_keyword_message();
    void reduce_assigment();

    int array_const();
    int code_block();

    bool terminal(TokenType);
    bool forward_check_fun(const std::vector<TokenType> &);
    bool any_terminal_fun(const std::vector<TokenType> &);

  public:
    ExpressionSyntaxAnalyzer(TokenStackIterator &);
    int analyze_expression(ast::Expression &);
};

enum class Precedence {
    Push,
    PushStop,
    Reduce,
    Function,
    Error,
    End,
};

enum class ExprType {
    _Expr = 128,
    _Stop,

    _dollar = 0,
    _id,
    _literal,
    _leftBracket,
    _rightBracket,
    _dot,
    _semicolom,
    _assigment,
    _colom,
    _leftBlock,
    _hash,
    _add,
    _sub,
    _mul,
    _div,
    _idiv,
    _mod,
    _and,
    _or,
    _eqIdentity,
    _neqIdentity,
    _eq,
    _neq,
    _lt,
    _gt,
    _lte,
    _gte,

};

template <class T> inline T ExpressionStack::pop() {
    ExpressionElem tmp = super::back();
    super::pop_back();
    return std::get<T>(tmp.value);
}
