#ifndef TOKEN_H
#define TOKEN_H

#include "error.h"
#include "messages.h"

typedef enum {

} eTokenType;

typedef enum {

} eTokenPayloadType;

union uTokenPayload {};

class cToken {
  public:
    eTokenType type;
    cToken *prev;
    cToken *next;

    eTokenPayloadType payloadType;
    uTokenPayload payload;
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
