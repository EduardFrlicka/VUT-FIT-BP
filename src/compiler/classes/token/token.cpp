#include "token.h"

Token::Token(FilePosition &_pos) : pos(_pos) {
    this->type = tokenNone;
    this->next = nullptr;
    this->prev = nullptr;
}

Token::~Token() {
}

bool Token::isspace() {
    switch (type) {
    case tokenWhiteSpace:
    case tokenEOL:
        return true;

    default:
        return false;
    }
}

std::string Token::type_string() {
    return type_string(type);
}

std::string Token::type_string(TokenType type) {
    std::string res;

#define CASE(type)                                                                                                                                                                                     \
    case type:                                                                                                                                                                                         \
        res = #type;                                                                                                                                                                                   \
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
    }
    return res;
}

void Token::print() {
    std::string printType;
    std::string printText;
    printText = text;
    printType = type_string();

    printf("%s:%u:%u: type: %-25s text: %s\n", pos.filename, pos.line, pos.col, printType.c_str(), printText.c_str());

#undef CASE
}