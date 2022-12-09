#ifndef TOKEN_H
#define TOKEN_H

#include "error.h"
#include "messages.h"
#include <string>

typedef enum {
    tokenNone = 0,
    tokenWhiteSpace,
    tokenEOL,
    tokenEOF,
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

    /* DEBUG data */
    const char *filename;
    const unsigned line;
    const unsigned col;

    Token(const char *_filename, unsigned _line, unsigned _col);
    ~Token();
};

class TokenStack {
  private:
    Token *head;
    Token *tail;
    Token *ptr;
    void pop();

  public:
    void append(Token *newToken);
    Token *peak();
    Token *next();
    Token *prev();

    void ptrHead();
    void ptrTail();

    TokenStack();
    ~TokenStack();
};

#endif /* TOKEN_H */
