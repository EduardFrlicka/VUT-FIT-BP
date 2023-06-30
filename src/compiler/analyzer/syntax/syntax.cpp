#include "syntax.h"
#include "messages.h"
#include "return_values.h"

SyntaxAnalyzer::SyntaxAnalyzer(Logger &_logger) : logger(_logger) {
}

int SyntaxAnalyzer::analyze_file(File *_file) {
    file = _file;

    return SUCCESS;
}

void SyntaxAnalyzer::next_token() {
    file->tokenStack.next();
    while (file->tokenStack.curr()->isspace())
        file->tokenStack.next();
}
