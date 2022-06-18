#ifndef TOKEN_H
#define TOKEN_H

#include "error.h"
#include "messages.h"

typedef enum {
    tokenTypeNone = 0,
} eTokenType;

typedef enum {
    tokenPayloadTypeNone = 0,
} eTokenPayloadType;

union uTokenPayload {};

class cToken {
  public:
    eTokenType type;
    cToken *prev;
    cToken *next;

    eTokenPayloadType payloadType;
    uTokenPayload *payload;

    /* DEBUG data */
    const char *filename;
    const unsigned line;
    const unsigned col;

    cToken(char *_filename, unsigned _line, unsigned _col);
    ~cToken();
};

class cTokenStack {
  private:
    cToken *head;
    cToken *tail;
    cToken *ptr;
    void pop();

  public:
    void append(cToken *newToken);
    cToken *peak();
    cToken *next();
    cToken *prev();

    void ptrHead();
    void ptrTail();

    cTokenStack();
    ~cTokenStack();
};

#endif /* TOKEN_H */
