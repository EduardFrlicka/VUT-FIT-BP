#include "lexical.h"
#include "return_values.h"

int LexicalAnalyzer::stateNumber(int c) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenNumber;

    if (c == 'r') {
        token.payload.number.convertRadix();
        nextState = &LexicalAnalyzer::stateNumberR;
        return SUCCESS;
    }

    if (c == 'e')
        nextState = &LexicalAnalyzer::stateNumberE;

    if (c == '.')
        stateNumberDot(c);

    if (token.payload.number.isdigit(c)) {
        nextState = &LexicalAnalyzer::stateNumber;
    }

    if (nextState != &LexicalAnalyzer::end)
        token.payload.number.append(c);

    return SUCCESS;
}

int LexicalAnalyzer::stateNumberR(int c) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenNumber;

    if (c == 'e')
        nextState = &LexicalAnalyzer::stateNumberE;

    if (c == '.')
        stateNumberDot(c);

    if (token.payload.number.isdigit(c)) {
        nextState = &LexicalAnalyzer::stateNumberR;
    }

    if (nextState != &LexicalAnalyzer::end)
        token.payload.number.append(c);

    return SUCCESS;
}

int LexicalAnalyzer::stateNumberDot(int c) {
    int c2;
    nextState = &LexicalAnalyzer::end;

    if (c == '.') {
        c2 = file->peek2();
        if (token.payload.number.isdigit(c2))
            nextState = &LexicalAnalyzer::stateNumberDot;
        return SUCCESS;
    }

    if (c == 'e')
        nextState = &LexicalAnalyzer::stateNumberE;

    if (token.payload.number.isdigit(c)) {
        nextState = &LexicalAnalyzer::stateNumberDot;
    }

    if (nextState != &LexicalAnalyzer::end)
        token.payload.number.append(c);

    return SUCCESS;
}

int LexicalAnalyzer::stateNumberE(int c) {
    nextState = &LexicalAnalyzer::end;

    if (isdigit(c)) {
        nextState = &LexicalAnalyzer::stateNumberE;
    }

    if (nextState != &LexicalAnalyzer::end)
        token.payload.number.append(c);

    return SUCCESS;
}

int LexicalAnalyzer::stateCharacter(int) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenChar;
    return SUCCESS;
}

int LexicalAnalyzer::stateIdentifier(int c) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenIdentifier;
    if (isalnum(c) || c == '_')
        nextState = &LexicalAnalyzer::stateIdentifier;
    return SUCCESS;
}

int LexicalAnalyzer::stateString(int c) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenString;
    if (c == '\'')
        nextState = &LexicalAnalyzer::stateStringOpen;
    return SUCCESS;
}

int LexicalAnalyzer::stateSymbol(int c) {
    nextState = &LexicalAnalyzer::end;
    token.type = tokenSymbol;
    if (isalnum(c))
        nextState = &LexicalAnalyzer::stateSymbol;
    return SUCCESS;
}
