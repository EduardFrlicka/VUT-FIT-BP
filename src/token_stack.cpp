#include "token.h"

cTokenStack::cTokenStack() {
    this->ptr = nullptr;
    this->head = nullptr;
    this->tail = nullptr;
}

cTokenStack::~cTokenStack() {
    while (this->head) {
        this->pop();
    }
}

void cTokenStack::pop() {
    if (!this->head) {
        WARNING(MSG_TOKEN_STACK_EMPTY);
        return;
    }

    cToken *tmp = this->head;

    if (this->head == this->tail)
        this->tail = nullptr;
    if (this->head == this->ptr)
        this->ptr = nullptr;

    this->head = this->head->next;
    this->head->prev = nullptr;

    delete tmp;
}

void cTokenStack::append(cToken *newToken) {
    if (!this->tail) {
        newToken->next = this->tail;
        newToken->prev = this->head;
        this->head = newToken;
        this->tail = newToken;
        return;
    }

    newToken->prev = this->tail;
    newToken->next = this->tail->next;

    this->tail->next = newToken;
    this->tail = newToken;
}

cToken *cTokenStack::peak() {
    if (this->ptr)
        WARNING(MSG_TOKEN_STACK_PTR_NULL);
    return this->ptr ? this->ptr->next : nullptr;
}

cToken *cTokenStack::prev() {
    if (this->ptr)
        this->ptr = this->ptr->prev;
    else
        WARNING(MSG_TOKEN_STACK_PTR_NULL);
    return this->ptr;
}

cToken *cTokenStack::next() {
    if (this->ptr)
        this->ptr = this->ptr->next;
    else
        WARNING(MSG_TOKEN_STACK_PTR_NULL);
    return this->ptr;
}

void cTokenStack::ptrHead() {
    this->ptr = this->head;
}

void cTokenStack::ptrTail() {
    this->ptr = this->tail;
}
