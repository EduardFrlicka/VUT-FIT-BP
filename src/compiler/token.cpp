#include "token.h"

cToken::cToken(const char *_filename, unsigned _line, unsigned _col) : filename(_filename), line(_line), col(_col) {
    this->type = tokenNone;
    this->next = nullptr;
    this->prev = nullptr;

    this->payloadType = tokenPayloadNone;
    this->payload = nullptr;
}

cToken::~cToken() {
}
