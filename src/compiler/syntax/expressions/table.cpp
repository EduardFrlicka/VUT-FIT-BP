#include "error_printer.h"
#include "expressions.h"
#include <iostream>

extern const std::vector<std::vector<std::vector<Precedence>>> table_smalltalk;

PrecedenceTable::PrecedenceTable(const std::vector<std::vector<std::vector<Precedence>>> &_table) {
    table = _table;
}

PrecedenceTable::PrecedenceTable() {
    table = table_smalltalk;
}

ExprType from_token(const Token &token) {
    switch (token.type) {
    case tokenIdentifier:
        return ExprType::_id;

    case tokenChar:
    case tokenFloat:
    case tokenInteger:
    case tokenSymbol:
    case tokenString:
    case tokenTrue:
    case tokenFalse:
    case tokenNil:
        return ExprType::_literal;

    case tokenLeftRoundBracket:
        return ExprType::_leftBracket;
    case tokenRightRoundBracket:
        return ExprType::_rightBracket;
    case tokenDot:
        return ExprType::_dot;
    case tokenSemicolon:
        return ExprType::_semicolom;
    case tokenAssign:
        return ExprType::_assigment;
    case tokenColon:
        return ExprType::_colom;
    case tokenLeftSquareBracket:
        return ExprType::_leftBlock;
    case tokenHash:
        return ExprType::_hash;
    case tokenAdd:
        return ExprType::_add;
    case tokenSub:
        return ExprType::_sub;
    case tokenMul:
        return ExprType::_mul;
    case tokenDiv:
        return ExprType::_div;
    case tokenIDiv:
        return ExprType::_idiv;
    case tokenMod:
        return ExprType::_mod;
    case tokenAnd:
        return ExprType::_and;
    case tokenOr:
        return ExprType::_or;
    case tokenEqIdentity:
        return ExprType::_eqIdentity;
    case tokenNotEqIdentity:
        return ExprType::_neqIdentity;
    case tokenEq:
        return ExprType::_eq;
    case tokenNotEq:
        return ExprType::_neq;
    case tokenLess:
        return ExprType::_lt;
    case tokenGreater:
        return ExprType::_gt;
    case tokenLessEq:
        return ExprType::_lte;
    case tokenGreaterEq:
        return ExprType::_gte;

    default:
        return ExprType::_dollar;
    }
    return ExprType();
}

Precedence PrecedenceTable::get(const ExpressionElem &elem, const Token &first, const Token &second) {
    return get(elem.type, from_token(first), from_token(second));
}

Precedence PrecedenceTable::get(ExprType left, ExprType first, ExprType second) {
    size_t left_index(static_cast<size_t>(left));
    size_t first_index(static_cast<size_t>(first));
    size_t second_index(static_cast<size_t>(second));

    // std::cout << _left << " " << _top << std::endl;

    if (table.size() <= left_index)
        internal_error("Index out of bounds in precedence table (%d >= %d)", table.size(), left_index);
    if (table[left_index].size() <= first_index)
        internal_error("Index out of bounds in precedence table (%d >= %d)", table[left_index].size(), first_index);

    if (table[left_index][first_index].size() == 1)
        return table[left_index][first_index][0];

    if (table[left_index][first_index].size() <= second_index)
        internal_error("Index out of bounds in precedence table (%d >= %d)", table[left_index][first_index].size(), second_index);

    return table[left_index][first_index][second_index];
}
