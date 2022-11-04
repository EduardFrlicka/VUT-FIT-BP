#include "lexical.h"
#include "return_values.h"

typedef enum {
    stateStart,
    stateError,
    // stateInternalErr,
    stateFinish,
    stateEOF,

    stateDollar,
    stateChar,

    stateStringOpen,
    stateString,
} lex_state;

int readToken(cFile *file);


int lex_analyze_file(cFile *file) {
    int res = SUCCESS;

    while (res == SUCCESS)
        res = readToken(file);

    return res == EOF ? SUCCESS : res;
}

int readToken(cFile *file) {
    lex_state state;
    lex_state nextState;
    cToken *token = file->newToken();
    int c;

    for (state = stateStart; state != stateError || state != stateFinish; state = nextState) {
        switch (state) {

        case stateStart:
            c = file->getchar();
            switch (c) {
            case EOF:
                nextState = stateEOF;
                break;

            case '$':
                nextState = stateDollar;
                break;

            case '\'':
                nextState = stateStringOpen;
                break;

            default:
                nextState = stateError;
            }
            break;

        case stateStringOpen:
            c = file->getchar();
            switch (c) {
            case '\'':
                nextState = stateString;
                break;
            case EOF:
                WARNING(MSG_LEX_UNEXPECTED_EOF);
                nextState = stateError;
                break;
            default:
                nextState = stateStringOpen;
                break;
            }
            break;

        case stateString:
            c = file->peakchar();
            if (c == '\'') {
                nextState = stateStringOpen;
            }
            break;

        case stateFinish:
            return SUCCESS;

        case stateError:
            // WARNING(MSG_LEX_UNEXPECTED_CHAR);
            return ERR_LEXICAL;

        default:
            ERROR(ERR_INTERNAL,"Not Implemented");
            // DEBUG("Not implemented");
            // return ERR_INTERNAL;+-
            // nextState = stateError;
            // break;
        }
    }
    return SUCCESS;
}
