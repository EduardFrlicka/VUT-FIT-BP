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

class TokenPayload {
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
    Token *peek();
    Token *next();
    Token *prev();

    void ptrHead();
    void ptrTail();

    void printStack();

    TokenStack();
    ~TokenStack();
};
