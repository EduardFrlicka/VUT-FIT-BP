#pragma once

#include "expressions_tree.h"
#include "syntax_tree_base.h"
#include "token.h"
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace AbstractSyntaxTree {

class TokenPair : public Base, public std::pair<std::optional<Token>, std::optional<Token>> {
  public:
    void print(int indent = 0) const;
};

class MultiSetTerm : public Base {
  public:
    std::optional<Token> value;

    class MultiSetList : public Base {
      public:
        std::vector<MultiSetTerm> values;
        std::optional<Token> tail;
        void print(int indent = 0) const;
    };

    std::optional<MultiSetList> list;
    void print(int indent = 0) const;
};

class MultiSetElem : public Base {
  public:
    std::optional<Token> count;
    MultiSetTerm term;
    void print(int indent = 0) const;
};

class MultiSet : public Base {
  public:
    std::vector<MultiSetElem> elements;
    void print(int indent = 0) const;
};

class ConditionPair : public Base, public std::pair<std::optional<Token>, MultiSet> {
  public:
    void print(int indent = 0) const;
};

class InitAction : public Base {
  public:
    std::vector<Token> temporaries;
    Expression expr;
    void print(int indent = 0) const;
};

class Action : public Base {
  public:
    std::vector<Token> temporaries;
    Expression expr;
    void print(int indent = 0) const;
};

class Guard : public Base {
  public:
    Expression expr;
    void print(int indent = 0) const;
};

class PostCondition : public Base {
  public:
    void print(int indent = 0) const;
    std::vector<ConditionPair> conditions;
};

class PreCondition : public Base {
  public:
    void print(int indent = 0) const;
    std::vector<ConditionPair> conditions;
};

class Condition : public Base {
  public:
    void print(int indent = 0) const;
    std::vector<ConditionPair> conditions;
};

class Transition : public Base {
  public:
    void print(int indent = 0) const;
    std::optional<Token> name;
    std::optional<Condition> conditions;
    std::optional<PreCondition> pre_conditions;
    std::optional<Guard> guard;
    std::optional<Action> action;
    std::optional<PostCondition> post_contitions;
};

class Place : public Base {
  public:
    void print(int indent = 0) const;
    std::optional<Token> name;
    std::optional<MultiSet> init_state;
    std::optional<InitAction> init_func;
};

class Message : public Base {
  public:
    std::optional<Token> unary;
    std::optional<TokenPair> binary;
    std::vector<TokenPair> keys;
    void print(int indent = 0) const;
};

class Net : public Base {
  public:
    std::vector<Place> places;
    std::vector<Transition> transitions;
    void print(int indent = 0) const;
};

class SynPort : public Base {
  public:
    Message message;

    std::optional<Condition> conditions;
    std::optional<PreCondition> pre_conditions;
    std::optional<Guard> guard;
    std::optional<PostCondition> post_contitions;

    void print(int indent = 0) const;
};

class Constructor : public Base {
  public:
    Message message;
    Net net;
    void print(int indent = 0) const;
};

class MethodNet : public Base {
  public:
    Message message;
    Net net;
    void print(int indent = 0) const;
};

class ObjectNet : public Base {
  public:
    Net net;
    void print(int indent = 0) const;
};

class ClassHead : public Base {
  public:
    std::optional<Token> derived;
    std::optional<Token> base;
    void print(int indent = 0) const;
};

class Class : public Base {
  public:
    ClassHead head;

    std::optional<ObjectNet> object;

    std::vector<Constructor> constructors;
    std::vector<MethodNet> methods;
    std::vector<SynPort> syn_ports;
    void print(int indent = 0) const;
};

class Classes : public Base {
  public:
    std::optional<Token> main;
    std::vector<Class> classes;
    void print(int indent = 0) const;
};

} // namespace AbstractSyntaxTree
