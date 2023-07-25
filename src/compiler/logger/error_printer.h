#pragma once

#include "file_position.h"
#include "identifier.h"
#include "logger.h"
#include "return_values.h"
#include "token.h"
#include <filesystem>

#ifdef DEBUG_PRINT
#define internal_error(format, ...)                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        logger.c_error(FilePosition(__FILE__, __LINE__, 0), "Internal error occured: " format __VA_OPT__(, ) __VA_ARGS__);                                                                             \
        exit(ERR_INTERNAL);                                                                                                                                                                            \
    } while (0)
#else
#define internal_error(format, ...)                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        logger.c_error("Internal error occured: " format __VA_OPT__(, ) __VA_ARGS__);                                                                                                                  \
        exit(ERR_INTERNAL);                                                                                                                                                                            \
    } while (0)
#endif

class ErrorPrinter;

extern ErrorPrinter error;

class ErrorPrinter {
  public:
    void undeclared_class(TokenStackIterator id);
    void class_redeclaration(Identifier declaration, TokenStackIterator redefined);

    void undeclared_variable(TokenStackIterator id);
    void undefined_variable(Identifier id, TokenStackIterator it);
    void variable_redeclaration(Identifier declaration, TokenStackIterator redefined);

    void message_redeclaration(Identifier declaration, TokenStackIterator redefined);
    void place_redeclaration(Identifier declaration, TokenStackIterator redefined);
    void transition_redeclaration(Identifier declaration, TokenStackIterator redefined);

    void place_not_found(TokenStackIterator id);

    void negative_count_in_multiset(TokenStackIterator it);

    void expression_primary_expected(TokenStackIterator begin, TokenStackIterator end);

    void expected_number(TokenStackIterator it);
    void expected_upper(TokenStackIterator id);
    void expected_lower(TokenStackIterator id);
};
