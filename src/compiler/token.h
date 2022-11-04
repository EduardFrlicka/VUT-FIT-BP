#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "error.h"
#include "messages.h"


typedef enum {
    tokenNone = 0,
} eTokenType;

typedef enum {
    tokenPayloadNone = 0,
    tokenPayloadNum,
    tokenPayloadStr,
    tokenPayloadChar,
    tokenPayloadSym,
    tokenPayloadBool,
    tokenPayloadNil,
} eTokenPayloadType;

union uTokenPayload {};

class cNumLiteral {
  private:
    double value;
    
  public:
    void appendChar();
    void convert();
    
    cNumLiteral();
    ~cNumLiteral();
};

class cStrLiteral {
  private:
};

class cCharLiteral {};

class cSymLiteral {};

class cBoolLiteral {};

class cNilLiteral {};
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

    cToken(const char *_filename, unsigned _line, unsigned _col);
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
