#include "lexical.h"
#include "return_values.h"

LexicalAnalyzer::LexicalAnalyzer(Logger &_logger) : logger(_logger) {
}

int LexicalAnalyzer::analyze_token() {
    int res;

    currState = &LexicalAnalyzer::start;
    nextState = &LexicalAnalyzer::start;

    token = file->newToken();

    while (currState != &LexicalAnalyzer::end) {
        res = (this->*currState)(file->peekchar());

        if (res)
            return res;

        if (nextState != &LexicalAnalyzer::end)
            token->text += file->getchar();

        currState = nextState;
    }
    return SUCCESS;
}

int LexicalAnalyzer::start(int c) {
    return SUCCESS;
}

int LexicalAnalyzer::end(int c) {
    return SUCCESS;
}
