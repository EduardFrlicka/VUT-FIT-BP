#include "error_printer.h"
#include <iostream>

#include <iomanip>
ErrorPrinter error;

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

void ErrorPrinter::variable_redeclaration(Identifier declaration, TokenStackIterator redefined) {
    std::cerr << "variable_redeclaration" << std::endl;
}

void ErrorPrinter::place_not_found(TokenStackIterator id) {
    std::cerr << "place_not_found" << std::endl;
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
