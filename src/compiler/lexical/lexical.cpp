#include "lexical.h"
#include "error.h"
#include "messages.h"
#include "return_values.h"

TokenStack &LexicalAnalyzer::analyze(const std::vector<std::string> &filenames) {
    int res = SUCCESS;
    for (auto file : filenames) {
        if (!res)
            res = analyze(file);
        else
            analyze(file);
    }

    if (res)
        throw "Lexical analysis failed";

    return tokenStack;
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
        ERROR(ERR_INTERNAL, "File not initialized");

    currState = &LexicalAnalyzer::start;
    nextState = &LexicalAnalyzer::start;

    token = new Token(file->getPos());
    tokenStack.append(token);

    while (currState != &LexicalAnalyzer::end) {
        currState = nextState;
        res = (this->*currState)(file->peek());

        if (res)
            return res;

        if (nextState != &LexicalAnalyzer::end)
            token->text += file->get();
    }
    return SUCCESS;
}

int LexicalAnalyzer::start(int c) {
    if (isdigit(c)) {

        token->payload.numberInit();
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
        nextState = &LexicalAnalyzer::stateLeftCurlyBracket;
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
        printf("ahoj %d\n", c);
        logger.error(file->getPos(), MSG_LEX_UNEXPECTED_CHAR);
        return ERR_LEXICAL;
        break;
    }

    return SUCCESS;
}

int LexicalAnalyzer::end(int c) {
    switch (token->type) {
    case tokenIdentifier:
        checkKeyword();
        break;

    case tokenNumber:
        token->payload.number.convert();
        break;
    default:
        break;
    }

    if (c == EOF)
        return EOF;
    return SUCCESS;
}
