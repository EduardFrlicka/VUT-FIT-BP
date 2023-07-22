#include "lexical.h"
#include "return_values.h"
#include <map>

void LexicalAnalyzer::checkKeyword() {
    using namespace std;

    static map<string, TokenType> keywords = {
        {"main", tokenMain},
        {"class", tokenClass},
        {"is_a", tokenIs_a},
        {"object", tokenObject},
        {"method", tokenMethod},
        {"constructor", tokenConstructor},
        {"sync", tokenSync},
        {"place", tokenPlace},
        {"init", tokenInit},
        {"trans", tokenTrans},
        {"cond", tokenCond},
        {"precond", tokenPrecond},
        {"postcond", tokenPostcond},
        {"guard", tokenGuard},
        {"action", tokenAction},
        {"nil", tokenNil},
        {"true", tokenTrue},
        {"false", tokenFalse},
        {},
    };

    /* check if token text is in keywords map (if token is a keyword) */
    if (keywords.find(token.text) == keywords.end())
        return;

    token.type = keywords[token.text];
}
