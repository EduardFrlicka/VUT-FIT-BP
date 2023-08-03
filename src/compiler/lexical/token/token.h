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

class TokenPayloadInteger {
  protected:
    std::string data = "";
    int radix = 10;

  public:
    long number;

    bool isdigit(int);
    void append(int);
    void convertRadix();
    void convert();
    std::string toString() const;
};

class TokenPayloadFloat : public TokenPayloadInteger {
  public:
    TokenPayloadFloat();
    TokenPayloadFloat(TokenPayloadInteger);
    double number;

    void convert();
    std::string toString() const;
};

class TokenPayloadSymbol {
  public:
    std::string value;
    void append(int);
    std::string toString() const;
};
class TokenPayloadString {
  public:
    std::string value;
    void append(int);
    std::string toString() const;
};
class TokenPayloadCharacter {
  public:
    char value;

    void set(int);
    std::string toString() const;
};

struct TokenPayload {
    TokenPayloadFloat float_number;
    TokenPayloadInteger integer_number;
    TokenPayloadSymbol symbol;
    TokenPayloadString string;
    TokenPayloadCharacter character;
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
    bool isspace() const;
    bool isliteral() const;

    void print() const;
};
