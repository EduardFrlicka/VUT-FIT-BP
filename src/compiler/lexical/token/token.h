#pragma once

#include "basic_identifier.h"
#include "file_position.h"
#include <deque>
#include <stack>
#include <string>

typedef enum {
    tokenNone = 0,
    tokenWhiteSpace,
    tokenEOL,
    tokenEOF,

    tokenIdentifier,

    /* literals */

    tokenChar,
    tokenFloat,
    tokenInteger,
    tokenSymbol,
    tokenString,
    tokenTrue,
    tokenFalse,
    tokenNil,

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
    tokenSemicolon,
    tokenAssign,
    tokenBacktick,
    tokenHash,

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

struct TokenPayload {
    TokenPayloadNumber number;
    BasicIdentifier id;
};

class Token;
class TokenStackIterator {
  private:
    std::stack<std::deque<Token>::iterator> stash;

  public:
    TokenStackIterator();
    TokenStackIterator(std::deque<Token> &);

    std::deque<Token>::iterator it;
    std::deque<Token>::iterator _begin;
    std::deque<Token>::iterator _end;

    Token &get();
    Token &get(int);
    Token &succ();

    void set(std::deque<Token>::iterator);
    void set(std::deque<Token>::iterator, std::deque<Token>::iterator, std::deque<Token>::iterator);

    void stash_push();

    void stash_pop();
    bool end();
};
class Token {
  public:
    TokenType type;
    FilePosition pos;
    TokenStackIterator it;

    TokenPayload payload;
    std::string text;

    // Token();
    Token(const FilePosition &);
    // Token(const Token &);

    ~Token();

    std::string type_string();
    static std::string type_string(TokenType);
    bool isspace();
    bool isliteral();

    void print() const;
};
