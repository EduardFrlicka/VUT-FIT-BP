#include "lexical.h"
#include "return_values.h"

int LexicalAnalyzer::stateLeftRoundBracket(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenLeftRoundBracket;
    return SUCCESS;
}

int LexicalAnalyzer::stateRightRoundBracket(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenRightRoundBracket;
    return SUCCESS;
}

int LexicalAnalyzer::stateLeftCurlyBracket(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenLeftCurlyBracket;
    return SUCCESS;
}

int LexicalAnalyzer::stateRightCurlyBracket(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenRightCurlyBracket;
    return SUCCESS;
}

int LexicalAnalyzer::stateLeftSquareBracket(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenLeftSquareBracket;
    return SUCCESS;
}

int LexicalAnalyzer::stateRightSquareBracket(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenRightSquareBracket;
    return SUCCESS;
}
