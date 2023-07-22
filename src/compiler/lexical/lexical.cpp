#include "lexical.h"
#include "error_printer.h"
#include "messages.h"
#include "return_values.h"
#include <iostream>

LexicalAnalyzer::LexicalAnalyzer(const std::vector<std::string> &filenames) : tokenStack(), token(FilePosition("")) {
    int res = SUCCESS;

    for (auto file : filenames) {
        if (!res)
            res = analyze(file);
        else
            analyze(file);
    }

    if (res)
        exit(res);

    push_eof();

    for (auto i = tokenStack.begin(); i < tokenStack.end(); i++) {
        i->it.set(i, tokenStack.begin(), tokenStack.end());
    }
}

TokenStackIterator LexicalAnalyzer::begin() {
    return TokenStackIterator(tokenStack);
}

int LexicalAnalyzer::analyze(const std::string &filename) {
    int res;

    file.emplace(filename);

    do {
        res = analyze_token();
    } while (!res);

    if (res != EOF)
        return res;

    return SUCCESS;
}

int LexicalAnalyzer::analyze_token() {
    int res;

    if (!file)
        internal_error("File not initialized");

    currState = &LexicalAnalyzer::start;
    nextState = &LexicalAnalyzer::start;

    token = Token(file->getPos());

    while (currState != &LexicalAnalyzer::end) {
        currState = nextState;
        res = (this->*currState)(file->peek());

        if (res)
            return res;

        if (nextState != &LexicalAnalyzer::end)
            token.text += file->get();
    }
    tokenStack.push_back(token);
    return SUCCESS;
}

void LexicalAnalyzer::push_eof() {
    token = Token(file->getPos());
    token.type = tokenEOF;

    tokenStack.push_back(token);
}

int LexicalAnalyzer::start(int c) {
    if (isdigit(c)) {

        stateNumber(c);
        return SUCCESS;
    }

    if (isalpha(c)) {
        nextState = &LexicalAnalyzer::stateIdentifier;
        return SUCCESS;
    }

    if (isblank(c)) {
        nextState = &LexicalAnalyzer::stateWhitespace;
        return SUCCESS;
    }

    switch (c) {
    case '$':
        nextState = &LexicalAnalyzer::stateDollar;
        break;

    case '\'':
        nextState = &LexicalAnalyzer::stateStringOpen;
        break;

    case '(':
        nextState = &LexicalAnalyzer::stateLeftRoundBracket;
        break;

    case ')':
        nextState = &LexicalAnalyzer::stateRightRoundBracket;
        break;

    case '{':
        nextState = &LexicalAnalyzer::stateLeftCurlyBracket;
        break;

    case '}':
        nextState = &LexicalAnalyzer::stateRightCurlyBracket;
        break;

    case '[':
        nextState = &LexicalAnalyzer::stateLeftSquareBracket;
        break;

    case ']':
        nextState = &LexicalAnalyzer::stateRightSquareBracket;
        break;

    case '+':
        nextState = &LexicalAnalyzer::stateAdd;
        break;

    case '-':
        nextState = &LexicalAnalyzer::stateSub;
        break;

    case '/':
        nextState = &LexicalAnalyzer::stateIDiv;
        break;

    case '*':
        nextState = &LexicalAnalyzer::stateMul;
        break;

    case '=':
        nextState = &LexicalAnalyzer::stateEq;
        break;

    case '<':
        nextState = &LexicalAnalyzer::stateLess;
        break;

    case '>':
        nextState = &LexicalAnalyzer::stateGreater;
        break;

    case '&':
        nextState = &LexicalAnalyzer::stateAnd;
        break;

    case '|':
        nextState = &LexicalAnalyzer::stateOr;
        break;

    case '\\':
        nextState = &LexicalAnalyzer::stateBackslash;
        break;

    case '~':
        nextState = &LexicalAnalyzer::stateTilde;
        break;

    case '.':
        nextState = &LexicalAnalyzer::stateDot;
        break;

    case ',':
        nextState = &LexicalAnalyzer::stateComma;
        break;

    case ':':
        nextState = &LexicalAnalyzer::stateColon;
        break;

    case ';':
        nextState = &LexicalAnalyzer::stateSemicolon;
        break;

    case '#':
        nextState = &LexicalAnalyzer::stateHash;
        break;

    case '`':
        nextState = &LexicalAnalyzer::stateBacktick;
        break;

    case '\n':
        nextState = &LexicalAnalyzer::stateEOL;
        break;

    default:
        logger.c_error(file->getPos(), MSG_LEX_UNEXPECTED_CHAR);
        return ERR_LEXICAL;
        break;
    }

    return SUCCESS;
}

int LexicalAnalyzer::end(int c) {
    switch (token.type) {
    case tokenIdentifier:
        checkKeyword();
        if (token.type == tokenIdentifier)
            token.payload.id = BasicIdentifier(token.text);
        break;

    case tokenInteger:
        token.payload.number.convert();
        break;
    case tokenFloat:
        token.payload.number.convert();
        break;
    default:
        break;
    }

    if (c == EOF)
        return EOF;
    return SUCCESS;
}
