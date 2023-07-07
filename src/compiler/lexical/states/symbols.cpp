#include "lexical.h"
#include "return_values.h"

int LexicalAnalyzer::stateDot(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenDot;
    return SUCCESS;
}

int LexicalAnalyzer::stateComma(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenComma;
    return SUCCESS;
}

int LexicalAnalyzer::stateColon(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenColon;
    if (c == '=')
        nextState = &LexicalAnalyzer::stateAssign;

    return SUCCESS;
}

int LexicalAnalyzer::stateAssign(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenAssign;
    return SUCCESS;
}

int LexicalAnalyzer::stateBacktick(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenBacktick;
    return SUCCESS;
}
