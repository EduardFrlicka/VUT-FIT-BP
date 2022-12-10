#include "token.h"

Token::Token(FilePosition &_pos) : pos(_pos) {
    this->type = tokenNone;
    this->next = nullptr;
    this->prev = nullptr;
}

Token::~Token() {
}
