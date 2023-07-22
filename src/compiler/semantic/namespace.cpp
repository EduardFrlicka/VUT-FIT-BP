#include "semantic.h"

NameSpace::NameSpace() {
    stack.emplace_back();
}

bool NameSpace::search(const Identifier &needle) {
    return search(needle.id.name);
}
bool NameSpace::search(const BasicIdentifier &needle) {
    return search(needle.name);
}

bool NameSpace::search(const std::string &needle) {
    for (auto it = stack.rbegin(); it != stack.rend(); it++) {
        if (it->find(needle) != it->end())
            return true;
    }

    return false;
}

Identifier &NameSpace::get(const Identifier &needle) {
    return get(needle.id.name);
}

Identifier &NameSpace::get(const BasicIdentifier &needle) {
    return get(needle.name);
}

Identifier &NameSpace::get(const std::string &needle) {
    for (auto it = stack.rbegin(); it != stack.rend(); it++) {
        if (it->find(needle) != it->end())
            return it->find(needle)->second;
    }
    return dummy;
}

void NameSpace::push(const Identifier &id) {
    stack.back().insert(std::make_pair(id.id.name, id));
}

void NameSpace::push_frame() {
    stack.emplace_back();
}

void NameSpace::pop_frame() {
    stack.pop_back();
}
