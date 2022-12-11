#include "token.h"

Token::Token(FilePosition &_pos) : pos(_pos) {
    this->type = tokenNone;
    this->next = nullptr;
    this->prev = nullptr;
}

Token::~Token() {
}

void Token::print() {
    std::string typeString;

#define CASE(type)                                                                                                                                                                                     \
    case type:                                                                                                                                                                                         \
        typeString = #type;                                                                                                                                                                            \
        break

    switch (type) {
        CASE(tokenNone);
        CASE(tokenWhiteSpace);
        CASE(tokenEOL);
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
    default:
        typeString = "unknown";
        break;
    }

    printf("%s:%u:%u: type: %-25s text: %s\n", pos.filename, pos.line, pos.col, typeString.c_str(), text.c_str());

#undef CASE
}