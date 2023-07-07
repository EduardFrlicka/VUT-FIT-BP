#include "token.h"
#include <iostream>

Token::Token(const FilePosition &_pos) : pos(_pos) {
    this->type = tokenNone;
    this->next = nullptr;
    this->prev = nullptr;
}

Token::Token(const Token &_token) : type(_token.type), prev(_token.prev), next(_token.next), text(_token.text), payload(_token.payload), pos(_token.pos) {
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

#undef CASE
}

void Token::print() {
    std::cout << "<Token>: " << (text == "\n" ? "EOL" : text) << std::endl;
}