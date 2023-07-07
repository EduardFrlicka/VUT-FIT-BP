#include "syntax_tree.h"
#include <iostream>

// using namespace ast;

#define INDENT_INCREMENT 2

#define print_header(type)                                                                                                                                                                             \
    do {                                                                                                                                                                                               \
        print_indent(indent);                                                                                                                                                                          \
        std::cout << "<" #type ">" << std::endl;                                                                                                                                                       \
    } while (0)

#define print_attribute(attribute)                                                                                                                                                                     \
    do {                                                                                                                                                                                               \
        print_indent(indent + INDENT_INCREMENT);                                                                                                                                                       \
        std::cout << #attribute ":" << std::endl;                                                                                                                                                      \
        (attribute).print(indent + 2 * INDENT_INCREMENT);                                                                                                                                              \
    } while (0)

#define print_optional(attribute)                                                                                                                                                                      \
    do {                                                                                                                                                                                               \
        if ((attribute).has_value()) {                                                                                                                                                                 \
            print_indent(indent + INDENT_INCREMENT);                                                                                                                                                   \
            std::cout << #attribute ":" << std::endl;                                                                                                                                                  \
            (attribute)->print(indent + 2 * INDENT_INCREMENT);                                                                                                                                         \
        }                                                                                                                                                                                              \
    } while (0)

#define print_token(attribute)                                                                                                                                                                         \
    do {                                                                                                                                                                                               \
        print_indent(indent + INDENT_INCREMENT);                                                                                                                                                       \
        std::cout << #attribute ": ";                                                                                                                                                                  \
        if ((attribute).has_value())                                                                                                                                                                   \
            (attribute)->print();                                                                                                                                                                      \
        else                                                                                                                                                                                           \
            std::cout << "Nada" << std::endl;                                                                                                                                                          \
    } while (0)

#define print_vector(attribute)                                                                                                                                                                        \
    do {                                                                                                                                                                                               \
        if ((attribute).size() > 0) {                                                                                                                                                                  \
            print_indent(indent + INDENT_INCREMENT);                                                                                                                                                   \
            std::cout << #attribute ":" << std::endl;                                                                                                                                                  \
        }                                                                                                                                                                                              \
        for (auto i : (attribute))                                                                                                                                                                     \
            i.print(indent + 2 * INDENT_INCREMENT);                                                                                                                                                    \
    } while (0)

namespace AbstractSyntaxTree {

void Base::print(int indent) {
    print_header(Base);
}

void Base::print_indent(int indent) {
    std::cout << std::string(indent, ' ');
}

void Classes::print(int indent) {
    print_header(Classes);

    print_token(main);

    print_vector(classes);
}

void Class::print(int indent) {
    print_header(Class);

    print_attribute(head);

    print_optional(object);

    print_vector(constructors);
    print_vector(methods);
    print_vector(syn_ports);
}

void ClassHead::print(int indent) {
    print_header(ClassHead);

    print_token(derived);
    print_token(base);
}

void ObjectNet::print(int indent) {
    print_header(ObjectNet);
    print_attribute(net);
}

void MethodNet::print(int indent) {
    print_header(MethodNet);
    print_attribute(message);
    print_attribute(net);
}

void Constructor::print(int indent) {
    print_header(Constructor);
    print_attribute(message);
    print_attribute(net);
}

void SynPort::print(int indent) {
    print_header(SynPort);
    print_attribute(message);
}

void Net::print(int indent) {
    print_header(Net);
    print_vector(places);
    print_vector(transitions);
}

void Message::print(int indent) {
    print_header(Message);

    print_token(method);
    print_optional(binary);
    print_vector(keys);
}

void Place::print(int indent) {
    print_header(Place);
    print_token(name);
    print_optional(init_state);
    print_optional(init_func);
}

void Init::print(int indent) {
    print_header(Init);
    print_attribute(action);
}

void Transition::print(int indent) {
    print_header(Transition);
    print_token(name);
    print_optional(conditions);
    print_optional(pre_conditions);
    print_optional(guard);
    print_optional(action);
    print_optional(post_contitions);
}

void Condition::print(int indent) {
    print_header(Condition);
    print_vector(conditions);
}

void PreCondition::print(int indent) {
    print_header(PreCondition);
    print_vector(conditions);
}

void PostCondition::print(int indent) {
    print_header(PostCondition);
    print_vector(conditions);
}

void Guard::print(int indent) {
    print_header(Guard);
}

void Action::print(int indent) {
    print_header(Action);
}

void InitAction::print(int indent) {
    print_header(InitAction);
}

void ConditionPair::print(int indent) {
    print_header(ConditionPair);
    print_token(first);
    print_attribute(second);
}

void MultiSet::print(int indent) {
    print_header(MultiSet);
    print_vector(elements);
}

void TokenPair::print(int indent) {
    print_header(TokenPair);
    print_token(first);
    print_token(second);
}

void MultiSetElem::print(int indent) {
    print_header(MultiSetElem);
    if (count.has_value())
        print_token(count);
    print_attribute(term);
}

void MultiSetTerm::print(int indent) {
    print_header(MultiSetTerm);
    if (value.has_value())
        print_token(value);
    else
        print_optional(list);
}

void MultiSetTerm::MultiSetList::print(int indent) {
    print_header(MultiSetList);
    print_vector(values);
    print_token(tail);
}

} // namespace AbstractSyntaxTree
