#include "error.h"
#include "messages.h"
#include "token.h"

TokenStack::TokenStack() {
    this->ptr = nullptr;
    this->head = nullptr;
    this->tail = nullptr;
}

TokenStack::~TokenStack() {
    while (this->head) {
        this->pop();
    }
}

void TokenStack::pop() {
    if (!this->head) {
        WARNING(MSG_TOKEN_STACK_EMPTY);
        return;
    }

    Token *tmp = this->head;

    if (this->head == this->tail)
        this->tail = nullptr;
    if (this->head == this->ptr)
        this->ptr = nullptr;

    this->head = this->head->next;
    if (this->head)
        this->head->prev = nullptr;

    delete tmp;
}

void TokenStack::append(Token *newToken) {
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

Token *TokenStack::curr() {
    return this->ptr;
}

Token *TokenStack::peek() {
    if (this->ptr)
        WARNING(MSG_TOKEN_STACK_PTR_NULL);
    return this->ptr ? this->ptr->next : nullptr;
}

Token *TokenStack::prev() {
    if (this->ptr)
        this->ptr = this->ptr->prev;
    else
        WARNING(MSG_TOKEN_STACK_PTR_NULL);
    return this->ptr;
}

Token *TokenStack::next() {
    if (this->ptr)
        this->ptr = this->ptr->next;
    else
        WARNING(MSG_TOKEN_STACK_PTR_NULL);
    return this->ptr;
}

void TokenStack::ptrHead() {
    this->ptr = this->head;
}

void TokenStack::ptrSet(Token *_ptr) {
    ptr = _ptr;
}

void TokenStack::ptrTail() {
    this->ptr = this->tail;
}

void TokenStack::printStack() {
    Token *savePtr;
    savePtr = ptr;

    for (ptrHead(); ptr; next()) {
        ptr->print();
    }

    ptr = savePtr;
}
