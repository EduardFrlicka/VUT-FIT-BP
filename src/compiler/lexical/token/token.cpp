#include "token.h"
#include <iostream>

Token::Token(const FilePosition &_pos) : pos(_pos) {
}

Token::~Token() {
}

bool Token::isspace() const {
    switch (type) {
    case tokenWhiteSpace:
    case tokenEOL:
        return true;

    default:
        return false;
    }
}

bool Token::isliteral() const {
    switch (type) {

    case tokenChar:
    case tokenFloat:
    case tokenInteger:
    case tokenSymbol:
    case tokenString:
    case tokenTrue:
    case tokenFalse:
    case tokenNil:
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
        CASE(tokenInteger);
        CASE(tokenFloat);
        CASE(tokenTrue);
        CASE(tokenFalse);
        CASE(tokenNil);
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
        CASE(tokenSemicolon);
        CASE(tokenAssign);
        CASE(tokenBacktick);
        CASE(tokenHash);
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

void Token::print() const {
    std::cout << "<Token>: " << (text == "\n" ? "EOL" : text) << std::endl;
}
