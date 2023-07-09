#include "expressions.h"
#include "expressions_tree.h"

using namespace ast;

/* E . E -> E          - expression concat */
void ExpressionSyntaxAnalyzer::reduce_expression_concat() {
    Expression second = stack.pop<Expression>();
    stack.pop();
    Expression first = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(ExpressionPair{first, second}));
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
    stack.push(Expression(CascadeUnary(recv, selector)));
}

/* E ; op E -> E       - binary cascade */
void ExpressionSyntaxAnalyzer::reduce_binary_cascade() {
    Expression argument = stack.pop<Expression>();
    Token selector = stack.pop<Token>();
    stack.pop();
    Expression recv = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(CascadeBinary(recv, selector, argument)));
}

/* E ; (id: E)+        - keyword cascade */
void ExpressionSyntaxAnalyzer::reduce_keyword_cascade() {
    Expression recv = stack.pop<Expression>();
    std::deque<Token> selector;
    std::deque<Expression> arguments;

    while (stack.try_match_top({ExprType::_id, ExprType::_colom, ExprType::_Expr})) {
        arguments.push_front(stack.pop<Expression>());
        stack.pop();
        selector.push_front(stack.pop<Token>());
        stack.pop();
    }
    stack.push(Expression(CascadeKeyWord(recv, selector, arguments)));
}

/* id -> E             - id */
void ExpressionSyntaxAnalyzer::reduce_id() {
    Token id = stack.pop<Token>();
    stack.pop();
    stack.push(Expression(ExpressionIdentifier(id)));
}

/* lit -> E            - lit */
void ExpressionSyntaxAnalyzer::reduce_lit() {
    Token lit = stack.pop<Token>();
    stack.pop();
    stack.push(Expression(ExpressionIdentifier(lit)));
}

/* (E) -> E            - bracket */
void ExpressionSyntaxAnalyzer::reduce_bracket() {
    stack.pop();
    Expression expr = stack.pop<Expression>();
    stack.pop();
    stack.pop();
    stack.push(expr);
}

/* E id -> E           - unary message - left */
void ExpressionSyntaxAnalyzer::reduce_unary_message() {
    Token selector = stack.pop<Token>();
    Expression recv = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(ExpressionUnary(recv, selector)));
}

/* E op E -> E         - binary message - left */
void ExpressionSyntaxAnalyzer::reduce_binary_message() {
    Expression argument = stack.pop<Expression>();
    Token selector = stack.pop<Token>();
    Expression recv = stack.pop<Expression>();
    stack.pop();
    stack.push(Expression(ExpressionBinary(recv, selector, argument)));
}

/*

 0 < 1 7 < E 1 8 < E 1 8 < E 1 8 E


*/

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

    stack.push(Expression(ExpressionKeyWord(recv, selector, arguments)));
}

/* id := E -> E        - assigment */
void ExpressionSyntaxAnalyzer::reduce_assigment() {
    Expression value = stack.pop<Expression>();
    stack.pop();
    Token target = stack.pop<Token>();
    stack.pop();
    stack.push(Expression(Assgiment(target, value)));
}