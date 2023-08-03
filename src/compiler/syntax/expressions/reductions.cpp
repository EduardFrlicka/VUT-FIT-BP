#include "expressions.h"
#include "expressions_tree.h"

using namespace ast;

/* E . E -> E          - expression concat */
void ExpressionSyntaxAnalyzer::reduce_expression_concat() {
    Expression second = stack.pop<Expression>();
    stack.pop();
    Expression first = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(ExpressionPair{first, second}, first.begin, second.end));
}

/* E . -> E            - expression end */
void ExpressionSyntaxAnalyzer::reduce_expression_end() {
    stack.pop();
    Expression expr = stack.pop<Expression>();
    stack.pop();
    stack.push(expr);
}

/* E ; id              - unary cascade */
void ExpressionSyntaxAnalyzer::reduce_unary_cascade() {
    Token selector = stack.pop<Token>();
    stack.pop();
    Expression recv = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(CascadeUnary(recv, selector), recv.begin, selector.it));
}

/* E ; op E -> E       - binary cascade */
void ExpressionSyntaxAnalyzer::reduce_binary_cascade() {
    Expression argument = stack.pop<Expression>();
    Token selector = stack.pop<Token>();
    stack.pop();
    Expression recv = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(CascadeBinary(recv, selector, argument), recv.begin, argument.end));
}

/* E ; (id: E)+        - keyword cascade */
void ExpressionSyntaxAnalyzer::reduce_keyword_cascade() {
    std::deque<Token> selector;
    std::deque<Expression> arguments;

    Expression recv = stack.pop<Expression>();

    while (stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_id, ExprType::_colom})) {
        stack.pop();
        selector.push_front(stack.pop<Token>());
        stack.pop();
        arguments.push_front(recv);
        recv = stack.pop<Expression>();
        stack.pop();
    }

    stack.push(Expression(CascadeKeyWord(recv, selector, arguments), recv.begin, arguments.back().end));
}

/* id -> E             - id */
void ExpressionSyntaxAnalyzer::reduce_id() {
    Token id = stack.pop<Token>();
    stack.pop();
    stack.push(Expression(ExpressionIdentifier(id), id.it));
}

/* lit -> E            - lit */
void ExpressionSyntaxAnalyzer::reduce_lit() {
    Token lit = stack.pop<Token>();
    stack.pop();
    stack.push(Expression(ExpressionValue(lit), lit.it));
}

/* (E) -> E            - bracket */
void ExpressionSyntaxAnalyzer::reduce_bracket() {
    Token back = stack.pop<Token>();
    Expression expr = stack.pop<Expression>();
    Token front = stack.pop<Token>();
    stack.pop();
    stack.push(Expression(Bracket(expr), front.it, back.it));
}

/* E id -> E           - unary message - left */
void ExpressionSyntaxAnalyzer::reduce_unary_message() {
    Token selector = stack.pop<Token>();
    Expression recv = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(ExpressionUnary(recv, selector), recv.begin, selector.it));
}

/* E op E -> E         - binary message - left */
void ExpressionSyntaxAnalyzer::reduce_binary_message() {
    Expression argument = stack.pop<Expression>();
    Token selector = stack.pop<Token>();
    Expression recv = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(ExpressionBinary(recv, selector, argument), recv.begin, argument.end));
}

/* E (id: E)+ -> E     - keyword message left */
void ExpressionSyntaxAnalyzer::reduce_keyword_message() {
    std::deque<Token> selector;
    std::deque<Expression> arguments;

    Expression recv = stack.pop<Expression>();

    while (stack.match_top({ExprType::_Expr, ExprType::_id, ExprType::_colom})) {
        stack.pop();
        selector.push_front(stack.pop<Token>());
        arguments.push_front(recv);
        recv = stack.pop<Expression>();
        stack.pop();
    }

    stack.push(Expression(ExpressionKeyWord(recv, selector, arguments), recv.begin, arguments.back().end));
}

/* id := E -> E        - assigment */
void ExpressionSyntaxAnalyzer::reduce_assigment() {
    Expression value = stack.pop<Expression>();
    stack.pop();
    Token target = stack.pop<Token>();
    stack.pop();
    stack.push(Expression(Assgiment(target, value), target.it, value.end));
}
