#ifndef LEXICAL_H
#define LEXICAL_H

#include "file.h"
#include "token.h"

/**
 * @brief Lexical analysis of file
 *
 * Calls function readToken until EOF is returned
 *
 * @param file pointer to cFile class. Analyzed tokens will be in tokenstack of this class
 * @return 0 if successfull, error code in case of some lexical error
 */
int lex_analyze_file(cFile *file);

#endif