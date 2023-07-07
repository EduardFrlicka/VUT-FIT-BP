#include "lexical.h"
#include "return_values.h"

int LexicalAnalyzer::stateWhitespace(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenWhiteSpace;
    if (isblank(c))
        nextState = &LexicalAnalyzer::stateWhitespace;
    return SUCCESS;
}

int LexicalAnalyzer::stateEOL(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenEOL;
    return SUCCESS;
}
