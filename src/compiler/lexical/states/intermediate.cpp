#include "lexical.h"
#include "messages.h"
#include "return_values.h"

#define EOFCHECK(c)                                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        if ((c) == EOF) {                                                                                                                                                                              \
            logger.error(file->getPos(), MSG_LEX_UNEXPECTED_EOF);                                                                                                                                      \
            return ERR_LEXICAL;                                                                                                                                                                        \
        }                                                                                                                                                                                              \
    } while (0)

#define EOLCHECK(c)                                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        if ((c) == '\n') {                                                                                                                                                                             \
            logger.error(file->getPos(), MSG_LEX_UNEXPECTED_EOL);                                                                                                                                      \
            return ERR_LEXICAL;                                                                                                                                                                        \
        }                                                                                                                                                                                              \
    } while (0)

int LexicalAnalyzer::stateBackslash(int c) {
    if (c == '\\') {
        nextState = &LexicalAnalyzer::stateMod;
        return SUCCESS;
    }

    EOLCHECK(c);
    EOFCHECK(c);
    logger.error(file->getPos(), MSG_LEX_UNEXPECTED_CHAR);
    return ERR_LEXICAL;
}

int LexicalAnalyzer::stateTilde(int c) {
    if (c == '~') {
        nextState = &LexicalAnalyzer::stateNotEq;
        return SUCCESS;
    }

    EOLCHECK(c);
    EOFCHECK(c);
    logger.error(file->getPos(), MSG_LEX_UNEXPECTED_CHAR);
    return ERR_LEXICAL;
}

int LexicalAnalyzer::stateDollar(int c) {
    EOFCHECK(c);
    EOLCHECK(c);
    if (isspace(c)) {
        logger.error(file->getPos(), MSG_LEX_UNEXPECTED_CHAR);
        return ERR_LEXICAL;
    }
    nextState = &LexicalAnalyzer::stateCharacter;
    return SUCCESS;
}

int LexicalAnalyzer::stateHash(int c) {
    EOFCHECK(c);
    EOLCHECK(c);

    if (!isalpha(c)) {
        logger.error(*token, MSG_LEX_UNEXPECTED_CHAR, c);
    }
    nextState = &LexicalAnalyzer::stateSymbol;
    return SUCCESS;
}

int LexicalAnalyzer::stateStringOpen(int c) {
    EOFCHECK(c);
    EOLCHECK(c);
    nextState = &LexicalAnalyzer::stateStringOpen;
    if (c == '\'')
        nextState = &LexicalAnalyzer::stateString;

    return SUCCESS;
}
