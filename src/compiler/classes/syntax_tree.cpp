#include "syntax_tree.h"

using namespace ast;

#define NULLCHECK(ptr, error)                                                                                                                                                                          \
    do {                                                                                                                                                                                               \
        if ((ptr) == nullptr) {                                                                                                                                                                        \
            error;                                                                                                                                                                                     \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
    } while (0)


void ast::print_tree(Class _class) {
    NULLCHECK(_class.head, "error msg");
}

void ast::print_tree(Classes _classes) {
    for (auto i : _classes.classes)
        print_tree(*i);
}

