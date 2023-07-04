#pragma once

#include "file_position.h"
#include <string>

typedef enum {
    tokenNone = 0,
    tokenWhiteSpace,
    tokenEOL,
    tokenEOF,

    /* literals */

    tokenChar,
    tokenNumber,
    tokenIdentifier,
    tokenSymbol,
    tokenString,

    /* brackets */

    tokenLeftRoundBracket,
    tokenRightRoundBracket,
    tokenLeftCurlyBracket,
    tokenRightCurlyBracket,
    tokenLeftSquareBracket,
    tokenRightSquareBracket,

    /* operators */

    tokenAdd,
    tokenSub,
    tokenIDiv,
    tokenMul,
    tokenEq,
    tokenNotEq,
    tokenEqIdentity,
    tokenNotEqIdentity,
    tokenLess,
    tokenGreater,
    tokenLessEq,
    tokenGreaterEq,
    tokenAnd,
    tokenOr,
    tokenMod,
    tokenDiv,

    /* Symbols */

    tokenDot,
    tokenComma,
    tokenColon,
    tokenAssign,
    tokenBacktick,

    /* Keywords */

    tokenMain,
    tokenClass,
    tokenIs_a,
    tokenObject,
    tokenMethod,
    tokenConstructor,
    tokenSync,
    tokenPlace,
    tokenInit,
    tokenTrans,
    tokenCond,
    tokenPrecond,
    tokenPostcond,
    tokenGuard,
    tokenAction,

} TokenType;

typedef enum {
    tokenPayloadNone = 0,
    tokenPayloadNum,
    tokenPayloadStr,
    tokenPayloadChar,
    tokenPayloadSym,
    tokenPayloadBool,
    tokenPayloadNil,
} TokenPayloadType;

class TokenPayloadNumber {
  public:
    std::string data = "";
    int radix = 10;
    long integer = -1, exponent = -1;
    double number;

    bool isdigit(int);
    void append(int);
    void convertRadix();
    void convert();
    std::string toString();
};

class TokenPayload {
  public:
    TokenPayloadNumber number;

    void numberInit();

  private:
    TokenPayloadType type;
};
class Token {
  public:
    TokenType type;
    Token *prev;
    Token *next;

    std::string text;

    TokenPayload payload;

    const FilePosition pos;

    Token(FilePosition &);
    ~Token();

    std::string type_string();
    static std::string type_string(TokenType);
    bool isspace();

    void print();
};

class TokenStack {
  private:
    Token *head;
    Token *tail;
    Token *ptr;
    void pop();

  public:
    void append(Token *newToken);
    Token *curr();
    Token *peek();
    Token *next();
    Token *prev();

    void ptrHead();
    void ptrTail();

    void printStack();

    TokenStack();
    ~TokenStack();
};
