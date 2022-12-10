#include "lexical.h"
#include "error.h"
#include "messages.h"
#include "return_values.h"

#define EOFCHECK(c)                                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        if ((c) == EOF) {                                                                                                                                                                              \
            logger.error_at(file->getPos(), MSG_LEX_UNEXPECTED_EOF);                                                                                                                                   \
            return ERR_LEXICAL;                                                                                                                                                                        \
        }                                                                                                                                                                                              \
    } while (0)

#define EOLCHECK(c)                                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        if ((c) == '\n') {                                                                                                                                                                             \
            logger.error_at(file->getPos(), MSG_LEX_UNEXPECTED_EOL);                                                                                                                                   \
            return ERR_LEXICAL;                                                                                                                                                                        \
        }                                                                                                                                                                                              \
    } while (0)

LexicalAnalyzer::LexicalAnalyzer(Logger &_logger) : logger(_logger) {
}

int LexicalAnalyzer::analyze_file(File *_file) {
    int res;
    file = _file;

    do {
        res = analyze_token();
    } while (!res);

    file = nullptr;

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

    token = file->newToken();
    DEBUG("%s:%u:%u", token->pos.filename, token->pos.line, token->pos.col);

    while (currState != &LexicalAnalyzer::end) {
        currState = nextState;
        res = (this->*currState)(file->peekchar());

        if (res)
            return res;

        if (nextState != &LexicalAnalyzer::end)
            token->text += file->getchar();
    }
    return SUCCESS;
}

int LexicalAnalyzer::start(int c) {
    if (isdigit(c)) {
        nextState = &LexicalAnalyzer::end;
        return SUCCESS;
    }

    if (isalpha(c)) {
        nextState = &LexicalAnalyzer::identifier;
        return SUCCESS;
    }

    if (isspace(c)) {
        nextState = &LexicalAnalyzer::whitespace;
        return SUCCESS;
    }

    switch (c) {
    case '$':
        nextState = &LexicalAnalyzer::dollar;
        break;

    case '\'':
        nextState = &LexicalAnalyzer::stropen;
        break;

    default:
        logger.error_at(file->getPos(), MSG_LEX_UNEXPECTED_CHAR);
        return ERR_LEXICAL;
        break;
    }

    return SUCCESS;
}

int LexicalAnalyzer::number(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenNumber;
    if (isdigit(c))
        nextState = &LexicalAnalyzer::number;

    return SUCCESS;
}
int LexicalAnalyzer::dollar(int c) {
    EOFCHECK(c);
    EOLCHECK(c);
    if (isspace(c)) {
        logger.error_at(file->getPos(), MSG_LEX_UNEXPECTED_CHAR);
        return ERR_LEXICAL;
    }
    nextState = &LexicalAnalyzer::character;
    return SUCCESS;
}
int LexicalAnalyzer::character(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenChar;
    return SUCCESS;
}

int LexicalAnalyzer::identifier(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenIdentifier;
    if (isalnum(c) || c == '_')
        nextState = &LexicalAnalyzer::identifier;
    return SUCCESS;
}

int LexicalAnalyzer::minus(int c) {
    nextState = &LexicalAnalyzer::end;
    return SUCCESS;
}

int LexicalAnalyzer::stropen(int c) {
    EOFCHECK(c);
    EOLCHECK(c);
    nextState = &LexicalAnalyzer::stropen;
    if (c == '\'')
        nextState = &LexicalAnalyzer::str;

    return SUCCESS;
}

int LexicalAnalyzer::str(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenString;
    if (c == '\'')
        nextState = &LexicalAnalyzer::stropen;
    return SUCCESS;
}

int LexicalAnalyzer::whitespace(int c) {
    nextState = &LexicalAnalyzer::end;
    token->type = tokenWhiteSpace;
    if (isspace(c))
        nextState = &LexicalAnalyzer::whitespace;
    return SUCCESS;
}

int LexicalAnalyzer::end(int c) {
    if (c == EOF)
        return EOF;
    return SUCCESS;
}
