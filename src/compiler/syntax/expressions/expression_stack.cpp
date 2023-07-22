#include "error_printer.h"
#include "expressions.h"
#include <iostream>

void ExpressionStack::print() {

    std::cout << "Stack: ";
    for (auto i = super::begin(); i != super::end(); i++)
        switch (i->type) {
        case ExprType::_Stop:
            std::cout << "< ";
            break;
        case ExprType::_Expr:
            std::cout << "E ";
            break;

        default:
            std::cout << (int)i->type << " ";
            break;
        }
    std::cout << std::endl;
}

ExpressionStack::ExpressionStack() : super() {
    super::push_back(ExpressionElem(ExprType::_dollar));
}

void ExpressionStack::reset() {
    super::clear();
    super::push_back(ExpressionElem(ExprType::_dollar));
}

const ExpressionElem &ExpressionStack::top() {

    auto i = super::rbegin();

    while (i != super::rend() && (i->type == ExprType::_Expr || i->type == ExprType::_Stop))
        i++;

    if (i == super::rend())
        internal_error("empty ExpressionStack");

    return *i;
}

ExpressionElem &ExpressionStack::top_elem() {
    return super::back();
}

bool ExpressionStack::match_top(const std::vector<ExprType> &types) {
    auto i = super::rbegin();

    for (auto type = types.rbegin(); type != types.rend() && i != super::rend(); type++) {
        if (i == super::rend())
            internal_error("empty ExpressionStack");

        if (*type != i->type)
            return false;
        i++;
    }

    return i->type == ExprType::_Stop;
}

bool ExpressionStack::try_match_top(const std::vector<ExprType> &types) {
    auto i = super::rbegin();

    for (auto type = types.rbegin(); type != types.rend() && i != super::rend(); type++) {
        std::cout << "Comp: " << (int)*type << " == " << (int)i->type << std::endl;
        if (i == super::rend())
            internal_error("empty ExpressionStack");

        if (*type != i->type)
            return false;
        i++;
    }

    std::cout << "jo" << std::endl;

    return true;
}

void ExpressionStack::pop() {
    super::pop_back();
}

void ExpressionStack::push(const Token &token) {
    super::push_back(ExpressionElem(token));
}

void ExpressionStack::push(const ast::Expression &expr) {
    super::push_back(ExpressionElem(expr));
}

void ExpressionStack::push_stop() {
    auto i = super::rbegin();

    while (i != super::rend() && i->type == ExprType::_Expr)
        i++;

    if (i == super::rend())
        internal_error("empty ExpressionStack");

    super::insert(i.base(), ExpressionElem(ExprType::_Stop));
}

ExpressionElem::ExpressionElem(ExprType _type) : type(_type), value(std::monostate()) {
    if (_type != ExprType::_dollar && _type != ExprType::_Stop)
        internal_error("Forbidden initialization of ExpressionElem");
}

ExpressionElem::ExpressionElem(const Token &token) : type(from_token(token)), value(token) {
}

ExpressionElem::ExpressionElem(const ast::Expression &expr) : type(ExprType::_Expr), value(expr) {
}
