#include "token.h"

cToken::cToken(char *_filename, unsigned _line, unsigned _col) : filename(_filename), line(_line), col(_col) {
    this->type = tokenTypeNone;
    this->next = nullptr;
    this->prev = nullptr;

    this->payloadType = tokenPayloadTypeNone;
    this->payload = nullptr;
}

cToken::~cToken() {
}
