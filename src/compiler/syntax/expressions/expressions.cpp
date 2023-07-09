#include "expressions.h"
#include "logger.h"
#include "messages.h"
#include "return_values.h"

/*
reduction rules:
    E . E -> E          - expression concat
    E . -> E            - expression end

    E ; id              - unary cascade
    E ; op E -> E       - binary cascade
    E ; (id: E)+        - keyword cascade

    id -> E             - id
    lit -> E            - lit

    (E) -> E            - bracket

    E id -> E           - unary message - left

    E op E -> E         - binary message - left

    E (id: E)+ -> E     - keyword message left

    id := E -> E        - assigment

precedence table
*/

ExpressionSyntaxAnalyzer::ExpressionSyntaxAnalyzer(TokenStackIterator &_token_stack) : token_stack(_token_stack) {
}

int ExpressionSyntaxAnalyzer::reduce() {

    /* E . E -> E          - expression concat */
    if (stack.match_top({ExprType::_Expr, ExprType::_dot, ExprType::_Expr})) {
        reduce_expression_concat();
        return SUCCESS;
    }

    /* E . -> E            - expression end */
    if (stack.match_top({ExprType::_Expr, ExprType::_dot})) {
        reduce_expression_end();
        return SUCCESS;
    }

    /* E ; id              - unary cascade */
    if (stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_id})) {
        reduce_unary_cascade();
        return SUCCESS;
    }

    /* E ; op E -> E       - binary cascade */
    if (stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_add, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_sub, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_mul, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_div, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_idiv, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_mod, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_and, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_or, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_eqIdentity, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_neqIdentity, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_eq, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_neq, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_lt, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_gt, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_lte, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_gte, ExprType::_Expr})) {
        reduce_binary_cascade();
        return SUCCESS;
    }

    /* E ; (id: E)+        - keyword cascade */
    if (stack.match_top({ExprType::_Expr, ExprType::_semicolom, ExprType::_id, ExprType::_colom, ExprType::_Expr})) {
        reduce_keyword_cascade();
        return SUCCESS;
    }

    /* id -> E             - id */
    if (stack.match_top({ExprType::_id})) {
        reduce_id();
        return SUCCESS;
    }

    /* lit -> E            - lit */
    if (stack.match_top({ExprType::_literal})) {
        reduce_lit();
        return SUCCESS;
    }

    /* (E) -> E            - bracket */
    if (stack.match_top({ExprType::_leftBracket, ExprType::_Expr, ExprType::_rightBracket})) {
        reduce_bracket();
        return SUCCESS;
    }

    /* E id -> E           - unary message - left */
    if (stack.match_top({ExprType::_Expr, ExprType::_id})) {
        reduce_unary_message();
        return SUCCESS;
    }

    /* E op E -> E         - binary message - left */
    if (stack.match_top({ExprType::_Expr, ExprType::_add, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_sub, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_mul, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_div, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_idiv, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_mod, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_and, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_or, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_eqIdentity, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_neqIdentity, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_eq, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_neq, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_lt, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_gt, ExprType::_Expr}) ||
        stack.match_top({ExprType::_Expr, ExprType::_lte, ExprType::_Expr}) || stack.match_top({ExprType::_Expr, ExprType::_gte, ExprType::_Expr})) {
        reduce_binary_message();
        return SUCCESS;
    }

    /* E (id: E)+ -> E     - keyword message left */
    if (stack.match_top({ExprType::_Expr, ExprType::_id, ExprType::_colom, ExprType::_Expr})) {
        reduce_keyword_message();
        return SUCCESS;
    }

    /* id := E -> E        - assigment */
    if (stack.match_top({ExprType::_id, ExprType::_assigment, ExprType::_Expr})) {
        reduce_assigment();
        return SUCCESS;
    }

    logger.c_error(token_stack.get(), MSG_SYN_UNEXPECTED_TOKEN);
    stack.print();
    return ERR_SYNTAX;
}

int ExpressionSyntaxAnalyzer::analyze_expression(ast::Expression &result) {
    int res;
    stack.reset();

    for (;;) {
        switch (table.get(stack.top(), token_stack.get(), token_stack.get(1))) {

        case Precedence::Push:
            stack.push(token_stack.get());
            token_stack.succ();
            break;

        case Precedence::PushStop:
            stack.push_stop();
            stack.push(token_stack.get());
            token_stack.succ();
            break;

        case Precedence::Reduce:
            res = reduce();
            if (res)
                return res;
            break;

        case Precedence::Error:
            logger.c_error(token_stack.get(), MSG_SYN_UNEXPECTED_TOKEN);
            break;

        case Precedence::End:
            if (stack.top_elem().type == ExprType::_Expr) {
                result = std::get<ast::Expression>(stack.top_elem().value);
                return SUCCESS;
            } else {
                logger.c_error(token_stack.get(), MSG_SYN_NO_EXPRESSION);
            }
            break;

        default:
            break;
        }
    }
    return SUCCESS;
}
