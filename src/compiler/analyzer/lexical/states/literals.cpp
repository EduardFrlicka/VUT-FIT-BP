#include "lexical.h"
#include "return_values.h"

int LexicalAnalyzer::stateNumber(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenNumber;
    if (isdigit(c))
        nextState = &LexicalAnalyzer::stateNumber;

    return SUCCESS;
}

int LexicalAnalyzer::stateCharacter(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenChar;
    return SUCCESS;
}

int LexicalAnalyzer::stateIdentifier(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenIdentifier;
    if (isalnum(c) || c == '_')
        nextState = &LexicalAnalyzer::stateIdentifier;
    return SUCCESS;
}

int LexicalAnalyzer::stateString(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenString;
    if (c == '\'')
        nextState = &LexicalAnalyzer::stateStringOpen;
    return SUCCESS;
}

int LexicalAnalyzer::stateWhitespace(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenWhiteSpace;
    if (isspace(c))
        nextState = &LexicalAnalyzer::stateWhitespace;
    return SUCCESS;
}

int LexicalAnalyzer::stateSymbol(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenSymbol;
    if (isalnum(c))
        nextState = &LexicalAnalyzer::stateSymbol;
    return SUCCESS;
}
