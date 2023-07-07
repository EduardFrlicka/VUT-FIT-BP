#pragma once

#include "token.h"
#include <optional>
#include <string>
#include <vector>

/*
namespace AbstractSyntaxTree {

enum Types {
    typeIdentifier,
    typeSymbol,
    typeChar,
    typeString,
    typeNumber,
    typeArray,
};

typedef std::string Identifier;
typedef std::string Symbol;
typedef char Character;
typedef std::string String;

struct Number {
    std::string *base;
    std::string *decimal;
    int *radix;
    int *exponent;
};

struct Array;
struct ArrayConst;

struct Elem {
    union {
        Identifier *identifier;
        Symbol *symbol;
        Character *character;
        String *string;
        Number *number;
        Array *array;
        ArrayConst *array_const;
    } elem;

    enum {
        elemIdentifier,
        elemSymbol,
        elemCharacter,
        elemString,
        elemNumber,
        elemArray,
    } type;
};

struct Array {
    std::vector<Elem *> elements;
};

struct ArrayConst {
    std::vector<Elem *> elements;
};

struct MultisetElem {
    enum {
        list,
    };
};
struct Multiset {};

struct Transition {};
struct Place {};
struct Net {};
struct ObjectNet {
    Net *net;
};
struct ClassHead {
    Token *token_name;
    Token *token_type;
    Identifier *name;
    Identifier *type;
};

struct Class {
    Token *token;
    ClassHead *head;
};

struct Classes {
    std::vector<Class *> classes;
};

void print_tree(Classes);
void print_tree(Class);

}; // namespace AbstractSyntaxTree
*/

namespace AbstractSyntaxTree {

class Base {
  public:
    virtual void print(int indent = 0);

  protected:
    void print_indent(int);
};

class TokenPair : public Base, public std::pair<std::optional<Token>, std::optional<Token>> {
  public:
    void print(int indent = 0);
};

class MultiSetTerm : public Base {
  public:
    std::optional<Token> value;

    class MultiSetList : public Base {
      public:
        std::vector<MultiSetTerm> values;
        std::optional<Token> tail;
        void print(int indent = 0);
    };

    std::optional<MultiSetList> list;
    void print(int indent = 0);
};

class MultiSetElem : public Base {
  public:
    std::optional<Token> count;
    MultiSetTerm term;
    void print(int indent = 0);
};

class MultiSet : public Base {
  public:
    std::vector<MultiSetElem> elements;
    void print(int indent = 0);
};

class ConditionPair : public Base, public std::pair<std::optional<Token>, MultiSet> {
  public:
    void print(int indent = 0);
};

class InitAction : public Base {
  public:
    void print(int indent = 0);
};

class Action : public Base {
  public:
    void print(int indent = 0);
};

class Guard : public Base {
  public:
    void print(int indent = 0);
};

class PostCondition : public Base {
  public:
    void print(int indent = 0);
    std::vector<ConditionPair> conditions;
};

class PreCondition : public Base {
  public:
    void print(int indent = 0);
    std::vector<ConditionPair> conditions;
};

class Condition : public Base {
  public:
    void print(int indent = 0);
    std::vector<ConditionPair> conditions;
};

class Transition : public Base {
  public:
    void print(int indent = 0);
    std::optional<Token> name;
    std::optional<Condition> conditions;
    std::optional<PreCondition> pre_conditions;
    std::optional<Guard> guard;
    std::optional<Action> action;
    std::optional<PostCondition> post_contitions;
};

class Init : public Base {
  public:
    void print(int indent = 0);
    InitAction action;
};

class Place : public Base {
  public:
    void print(int indent = 0);
    std::optional<Token> name;
    std::optional<MultiSet> init_state;
    std::optional<Init> init_func;
};

class Message : public Base {
  public:
    std::optional<Token> method;
    std::optional<TokenPair> binary;
    std::vector<TokenPair> keys;
    void print(int indent = 0);
};

class Net : public Base {
  public:
    std::vector<Place> places;
    std::vector<Transition> transitions;
    void print(int indent = 0);
};

class SynPort : public Base {
  public:
    Message message;
    void print(int indent = 0);
};

class Constructor : public Base {
  public:
    Message message;
    Net net;
    void print(int indent = 0);
};

class MethodNet : public Base {
  public:
    Message message;
    Net net;
    void print(int indent = 0);
};

class ObjectNet : public Base {
  public:
    Net net;
    void print(int indent = 0);
};

class ClassHead : public Base {
  public:
    std::optional<Token> derived;
    std::optional<Token> base;
    void print(int indent = 0);
};

class Class : public Base {
  public:
    ClassHead head;

    std::optional<ObjectNet> object;

    std::vector<Constructor> constructors;
    std::vector<MethodNet> methods;
    std::vector<SynPort> syn_ports;
    void print(int indent = 0);
};

class Classes : public Base {
  public:
    std::optional<Token> main;
    std::vector<Class> classes;
    void print(int indent = 0);
};

} // namespace AbstractSyntaxTree

namespace ast = AbstractSyntaxTree;
