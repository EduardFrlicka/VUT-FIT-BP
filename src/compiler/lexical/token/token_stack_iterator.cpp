#include "token.h"

TokenStackIterator::TokenStackIterator() {
}

TokenStackIterator::TokenStackIterator(std::deque<Token> &stack) {
    it = stack.begin();
    _begin = stack.begin();
    _end = stack.end();
}

Token &TokenStackIterator::get() {
    // TODO: insert return statement here
    return *it;
}

Token &TokenStackIterator::get(int count) {
    auto save = it;
    auto res = it;
    if (count > 0)
        for (auto i = 0; i < count; i++) {
            do {
                it++;
            } while (it < _end && it->isspace());
        }
    else
        for (auto i = 0; i > count; i--) {
            do {
                it--;
            } while (it >= _begin && it->isspace());
        }

    res = it;
    it = save;

    return *res;
}

Token &TokenStackIterator::succ() {
    do {
        it++;
    } while (it < _end && it->isspace());

    return *it;
}

void TokenStackIterator::set(std::deque<Token>::iterator _it) {
    it = _it;
}

void TokenStackIterator::set(std::deque<Token>::iterator _it, std::deque<Token>::iterator __begin, std::deque<Token>::iterator __end) {
    it = _it;
    _begin = __begin;
    _end = __end;
}

void TokenStackIterator::stash_push() {
    stash.push(it);
}

void TokenStackIterator::stash_pop() {
    it = stash.top();
    stash.pop();
}

bool TokenStackIterator::end() {
    return it == _end;
}
