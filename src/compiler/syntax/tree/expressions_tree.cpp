#include "expressions_tree.h"
#include "error_printer.h"
#include <iostream>
#include <map>

bool AbstractSyntaxTree::Expression::isprimary() const {
    switch (value->index()) {
    case 4:
    case 5:
    case 6:
    case 10:
        return true;
    case 11:
        break;
    }
    return false;
}

bool AbstractSyntaxTree::Expression::issecundary() const {
    switch (value->index()) {
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        return true;
    case 11:
        break;
    }
    return false;
}

void AbstractSyntaxTree::Expression::print(int indent) const {
    if (indent) {
        print_indent(indent);
        std::cout << "<Expression>: ";
    }

    if (!value)
        internal_error("Malformed Expression class");

    switch (value->index()) {

    case 0:
        std::get<ExpressionPair>(*value).print();
        break;
    case 1:
        std::get<CascadeUnary>(*value).print();
        break;
    case 2:
        std::get<CascadeBinary>(*value).print();
        break;
    case 3:
        std::get<CascadeKeyWord>(*value).print();
        break;
    case 4:
        std::get<ExpressionIdentifier>(*value).print();
        break;
    case 5:
        std::get<ExpressionValue>(*value).print();
        break;
    case 6:
        std::get<ExpressionUnary>(*value).print();
        break;
    case 7:
        std::get<ExpressionBinary>(*value).print();
        break;
    case 8:
        std::get<ExpressionKeyWord>(*value).print();
        break;
    case 9:
        std::get<Assgiment>(*value).print();
        break;
    case 10:
        std::get<Bracket>(*value).print();
        break;
    case 11:
        std::get<CodeBlock>(*value).print();
        break;
    case 12:
        std::get<ConstArray>(*value).print();
        break;
    }

    if (indent) {
        std::cout << std::endl;
    }
}

AbstractSyntaxTree::ExpressionPair::ExpressionPair(const Expression &_first, const Expression &_second) : first(_first), second(_second) {
}

void AbstractSyntaxTree::ExpressionPair::print(int indent) {
    first.print();
    std::cout << ".";
    second.print();
}

AbstractSyntaxTree::CascadeUnary::CascadeUnary(const Expression &_recv, const Token &_selector) : recv(_recv), message_selector(_selector) {
}

void AbstractSyntaxTree::CascadeUnary::print(int indent) {
    recv.print();
    std::cout << "; " << message_selector.text;
}

AbstractSyntaxTree::CascadeBinary::CascadeBinary(const Expression &_recv, const Token &_selector, const Expression &_argument) : recv(_recv), message_selector(_selector), argument(_argument) {
}

void AbstractSyntaxTree::CascadeBinary::print(int indent) {
    recv.print();
    std::cout << "; " << message_selector.text;
    argument.print();
}

AbstractSyntaxTree::CascadeKeyWord::CascadeKeyWord(const Expression &_recv, const std::deque<Token> &_selector, const std::deque<Expression> &_arguments)
    : recv(_recv), selector(_selector), arguments(_arguments) {
}

void AbstractSyntaxTree::CascadeKeyWord::print(int indent) {
    recv.print();
    for (auto i = 0ul; i < selector.size(); i++) {
        std::cout << "; " << selector[i].text << ":(";
        arguments[i].print();
        std::cout << ")";
    }
}

AbstractSyntaxTree::ExpressionIdentifier::ExpressionIdentifier(const Token &_value) : value(_value) {
}

void AbstractSyntaxTree::ExpressionIdentifier::print(int indent) {
    std::cout << value.text;
}
AbstractSyntaxTree::ExpressionValue::ExpressionValue(const Token &_value) : value(_value) {
}

void AbstractSyntaxTree::ExpressionValue::print(int indent) {
    std::cout << value.text;
}

AbstractSyntaxTree::ExpressionUnary::ExpressionUnary(const Expression &_recv, const Token &_selector) : recv(_recv), message_selector(_selector) {
}

void AbstractSyntaxTree::ExpressionUnary::print(int indent) {
    recv.print();
    std::cout << " " << message_selector.text;
}

AbstractSyntaxTree::ExpressionBinary::ExpressionBinary(const Expression &_recv, const Token &_selector, const Expression &_argument) : recv(_recv), message_selector(_selector), argument(_argument) {
}

void AbstractSyntaxTree::ExpressionBinary::print(int indent) {
    recv.print();
    std::cout << " " << message_selector.text;
    argument.print();
}

AbstractSyntaxTree::ExpressionKeyWord::ExpressionKeyWord(const Expression &_recv, const std::deque<Token> &_selector, const std::deque<Expression> &_arguments)
    : recv(_recv), selector(_selector), arguments(_arguments) {
}

void AbstractSyntaxTree::ExpressionKeyWord::print(int indent) {
    recv.print();
    for (auto i = 0ul; i < selector.size(); i++) {
        std::cout << " " << selector[i].text << ":(";
        arguments[i].print();
        std::cout << ")";
    }
}

AbstractSyntaxTree::Assgiment::Assgiment(const Token &_target, const Expression &_value) : target(_target), value(_value) {
}

void AbstractSyntaxTree::Assgiment::print(int indent) {
    std::cout << target.text << ":=";
    value.print();
}

AbstractSyntaxTree::Bracket::Bracket(const Expression &_expr) : expr(_expr) {
}

void AbstractSyntaxTree::Bracket::print(int indent) {
    std::cout << "(";
    expr.print();
    std::cout << ")";
}

AbstractSyntaxTree::CodeBlock::CodeBlock(const std::deque<Token> &_arguments, const std::deque<Token> &_temps, const Expression &_expr) : arguments(_arguments), temps(_temps), expr(_expr) {
}

void AbstractSyntaxTree::CodeBlock::print(int indent) {
    std::cout << "[";

    for (auto i : arguments)
        std::cout << ":" << i.text << " ";
    std::cout << "|";

    for (auto i : temps)
        std::cout << i.text << " ";
    std::cout << "|";

    expr.print();
    std::cout << "]";
}

AbstractSyntaxTree::ConstArray::ConstArray(const std::deque<Token> &_values) : elements(_values) {
}

void AbstractSyntaxTree::ConstArray::print(int indent) {
    std::cout << "#(";

    for (auto i : elements)
        i.print();
    std::cout << ")";
}

AbstractSyntaxTree::Expression::Expression() {
}

AbstractSyntaxTree::Expression::Expression(const ExpressionPair &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}

AbstractSyntaxTree::Expression::Expression(const CascadeUnary &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const CascadeBinary &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const CascadeKeyWord &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const ExpressionIdentifier &val, TokenStackIterator it) {
    begin = it;
    end = it;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const ExpressionValue &val, TokenStackIterator it) {
    begin = it;
    end = it;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const ExpressionUnary &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const ExpressionBinary &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const ExpressionKeyWord &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
AbstractSyntaxTree::Expression::Expression(const Assgiment &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}

AbstractSyntaxTree::Expression::Expression(const Bracket &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}

AbstractSyntaxTree::Expression::Expression(const CodeBlock &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}

AbstractSyntaxTree::Expression::Expression(const ConstArray &val, TokenStackIterator _begin, TokenStackIterator _end) {
    begin = _begin;
    end = _end;
    value = std::make_shared<ExprVal>(ExprVal(val));
}
