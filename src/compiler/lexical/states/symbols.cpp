#include "lexical.h"
#include "return_values.h"

int LexicalAnalyzer::stateHash(int c) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenHash;
    if (isalpha(c)) {
        token.payload.symbol.append(c);
        nextState = &LexicalAnalyzer::stateSymbol;
    }
    if (c == '\'')
        nextState = &LexicalAnalyzer::stateSymbolOpen;

    return SUCCESS;
}

int LexicalAnalyzer::stateDot(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenDot;
    return SUCCESS;
}

int LexicalAnalyzer::stateComma(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenComma;
    return SUCCESS;
}

int LexicalAnalyzer::stateColon(int c) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenColon;
    if (c == '=')
        nextState = &LexicalAnalyzer::stateAssign;

    return SUCCESS;
}

int LexicalAnalyzer::stateSemicolon(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenSemicolon;
    return SUCCESS;
}

int LexicalAnalyzer::stateAssign(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenAssign;
    return SUCCESS;
}

int LexicalAnalyzer::stateBacktick(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenBacktick;
    return SUCCESS;
}
