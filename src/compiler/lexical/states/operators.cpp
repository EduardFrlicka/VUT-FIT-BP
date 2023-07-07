#include "lexical.h"
#include "messages.h"
#include "return_values.h"

int LexicalAnalyzer::stateAdd(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenAdd;
    return SUCCESS;
}

int LexicalAnalyzer::stateSub(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenSub;
    return SUCCESS;
}

int LexicalAnalyzer::stateIDiv(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenIDiv;
    if (c == '/')
        nextState = &LexicalAnalyzer::stateDiv;

    return SUCCESS;
}

int LexicalAnalyzer::stateMul(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenMul;
    return SUCCESS;
}

int LexicalAnalyzer::stateEq(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenEq;
    if (c == '=')
        nextState = &LexicalAnalyzer::stateEqIdentity;
    return SUCCESS;
}

int LexicalAnalyzer::stateNotEq(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenNotEq;
    if (c == '=')
        nextState = &LexicalAnalyzer::stateNotEqIdentity;
    return SUCCESS;
}

int LexicalAnalyzer::stateEqIdentity(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenEqIdentity;
    return SUCCESS;
}

int LexicalAnalyzer::stateNotEqIdentity(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenNotEqIdentity;
    return SUCCESS;
}

int LexicalAnalyzer::stateLess(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenLess;
    if (c == '=')
        nextState = &LexicalAnalyzer::stateLessEq;
    return SUCCESS;
}

int LexicalAnalyzer::stateGreater(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenGreater;
    if (c == '=')
        nextState = &LexicalAnalyzer::stateGreaterEq;
    return SUCCESS;
}

int LexicalAnalyzer::stateLessEq(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenLessEq;
    return SUCCESS;
}

int LexicalAnalyzer::stateGreaterEq(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenGreaterEq;
    return SUCCESS;
}

int LexicalAnalyzer::stateAnd(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenAnd;
    return SUCCESS;
}

int LexicalAnalyzer::stateOr(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenOr;
    return SUCCESS;
}

int LexicalAnalyzer::stateMod(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenMod;
    return SUCCESS;
}

int LexicalAnalyzer::stateDiv(int) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenDiv;
    return SUCCESS;
}
