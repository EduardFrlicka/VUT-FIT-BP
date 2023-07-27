#include "error_printer.h"
#include <iostream>

#include <iomanip>
ErrorPrinter error;

void ErrorPrinter::undeclared_class(TokenStackIterator id) {
    logger.c_error(id, "Use of undeclared class name");
}

void ErrorPrinter::class_redeclaration(Identifier defined, TokenStackIterator redefined) {
    std::cerr << "class_redeclaration" << std::endl;
}

void ErrorPrinter::message_redeclaration(Identifier defined, TokenStackIterator redefined) {
    std::cerr << "message_redeclaration" << std::endl;
}

void ErrorPrinter::place_redeclaration(Identifier defined, TokenStackIterator redefined) {
    std::cerr << "place_redeclaration" << std::endl;
}

void ErrorPrinter::transition_redeclaration(Identifier defined, TokenStackIterator redefined) {
    std::cerr << "transition_redeclaration" << std::endl;
}

void ErrorPrinter::argument_redeclaration(Identifier declaration, TokenStackIterator redefined) {
    std::cerr << "argument_redeclaration" << std::endl;
}

void ErrorPrinter::implicit_declaration_variable(TokenStackIterator id) {
    logger.c_warning(id, "Implicit declaration of variable");
}

void ErrorPrinter::undeclared_variable(TokenStackIterator id) {
    logger.c_error(id, "Use of undeclared variable");
}

void ErrorPrinter::undefined_variable(Identifier id, TokenStackIterator it) {
    logger.c_error(it, "Use of undefined variable");
    logger.c_note(id.declaration_begin, "Variable declared:");
}

void ErrorPrinter::undefined_variable_warn(Identifier id, TokenStackIterator it) {
    logger.c_warning(it, "Use of undefined variable");
    logger.c_note(id.declaration_begin, "Variable declared:");
}

void ErrorPrinter::variable_redeclaration(Identifier declaration, TokenStackIterator redefined) {
    std::cerr << "variable_redeclaration" << std::endl;
}

void ErrorPrinter::undeclared_place(TokenStackIterator id) {
    std::cerr << "undeclared_place" << std::endl;
}

void ErrorPrinter::undeclared_return(TokenStackIterator id) {
    std::cerr << "undeclared_place result" << std::endl;
}

void ErrorPrinter::negative_count_in_multiset(TokenStackIterator it) {
    std::cerr << "negative_count_in_multiset" << std::endl;
}

void ErrorPrinter::expression_primary_expected(TokenStackIterator begin, TokenStackIterator end) {
    std::cerr << "expression_primary_expected" << std::endl;
    logger.c_note(begin.get(), "baf");
}

void ErrorPrinter::expected_number(TokenStackIterator it) {
    std::cerr << "expected_number" << std::endl;
}

void ErrorPrinter::expected_upper(TokenStackIterator id) {
    std::cerr << "exp upper" << std::endl;
}

void ErrorPrinter::expected_lower(TokenStackIterator id) {
    std::cerr << "exp lower" << std::endl;
}
