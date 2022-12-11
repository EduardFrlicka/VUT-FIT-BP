#include "token.h"

Token::Token(FilePosition &_pos) : pos(_pos) {
    this->type = tokenNone;
    this->next = nullptr;
    this->prev = nullptr;
}

Token::~Token() {
}

void Token::print() {
    std::string printType;
    std::string printText;
    printText = text;

#define CASE(type)                                                                                                                                                                                     \
    case type:                                                                                                                                                                                         \
        printType = #type;                                                                                                                                                                             \
        break

    switch (type) {
        CASE(tokenNone);
        CASE(tokenWhiteSpace);

    case tokenEOL:
        printType = "tokenEOL";
        printText = "";
        break;

        CASE(tokenEOF);
        CASE(tokenChar);
        CASE(tokenNumber);
        CASE(tokenIdentifier);
        CASE(tokenSymbol);
        CASE(tokenString);
        CASE(tokenLeftRoundBracket);
        CASE(tokenRightRoundBracket);
        CASE(tokenLeftCurlyBracket);
        CASE(tokenRightCurlyBracket);
        CASE(tokenLeftSquareBracket);
        CASE(tokenRightSquareBracket);
        CASE(tokenAdd);
        CASE(tokenSub);
        CASE(tokenIDiv);
        CASE(tokenMul);
        CASE(tokenEq);
        CASE(tokenNotEq);
        CASE(tokenEqIdentity);
        CASE(tokenNotEqIdentity);
        CASE(tokenLess);
        CASE(tokenGreater);
        CASE(tokenLessEq);
        CASE(tokenGreaterEq);
        CASE(tokenAnd);
        CASE(tokenOr);
        CASE(tokenMod);
        CASE(tokenDiv);
        CASE(tokenDot);
        CASE(tokenComma);
        CASE(tokenColon);
        CASE(tokenAssign);
        CASE(tokenBacktick);
        CASE(tokenMain);
        CASE(tokenClass);
        CASE(tokenIs_a);
        CASE(tokenObject);
        CASE(tokenMethod);
        CASE(tokenConstructor);
        CASE(tokenSync);
        CASE(tokenPlace);
        CASE(tokenInit);
        CASE(tokenTrans);
        CASE(tokenCond);
        CASE(tokenPrecond);
        CASE(tokenPostcond);
        CASE(tokenGuard);
        CASE(tokenAction);
    default:
        printType = "unknown";
        break;
    }

    printf("%s:%u:%u: type: %-25s text: %s\n", pos.filename, pos.line, pos.col, printType.c_str(), printText.c_str());

#undef CASE
}