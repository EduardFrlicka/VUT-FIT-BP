#pragma once
#include "identifier.h"
#include "semantic_expression_graph.h"
#include "semantic_graph_base.h"
#include <deque>
#include <optional>

namespace AbstractSemanticGraph {

class MultiSetTerm;
class MultiSetList : public Base {
  public:
    std::deque<MultiSetTerm> elements;
    std::optional<Identifier> tail;
};
class MultiSetTerm : public Base {
  public:
    std::optional<MultiSetList> list;
    std::optional<Literal> literal;
    std::optional<Variable> variable;
};

class MultiSetCount : public Base {
  private:
    std::variant<int, Variable> _value;

  public:
    MultiSetCount();
    MultiSetCount(int value);
    MultiSetCount(Variable value);

    bool is_int() const;
    bool is_variable() const;
    int get_int() const;
    Variable get_variable() const;
};

class MultiSetElemPair : public Base {
  public:
    MultiSetCount count;
    MultiSetTerm term;
};

class MultiSet : public Base {
  public:
    std::deque<MultiSetElemPair> elements;
};

class CondPair : public Base {
  public:
    Identifier place;
    MultiSet edge_expression;
};

class PreCondPair : public Base {
  public:
    PreCondPair(const CondPair &);
    Identifier place;
    MultiSet edge_expression;
};

class Guard : public Base {
  public:
    Expressions expression;
};

class Action : public Base {
  public:
    std::deque<Identifier> variables;
    Expression expression;
};

class PostCondPair : public Base {
  public:
    PostCondPair(const CondPair &);
    Identifier place;
    MultiSet edge_expression;
};

class Transition : public Base {
  public:
    Identifier name;
    std::deque<Identifier> variables;
    std::deque<PreCondPair> pre_conditions;
    std::deque<CondPair> conditions;
    std::deque<PostCondPair> post_conditions;
    std::optional<Guard> guard;
    std::optional<Action> action;
};
class Place : public Base {
  public:
    Identifier name;
    std::optional<MultiSet> init_state;
    std::optional<Action> init_action;
};

class Net : public Base {
  public:
    std::deque<Place> places;
    std::deque<Transition> transitions;
};

class Method : public Base {
  public:
    Identifier selector;
    std::deque<Identifier> arguments;
    Net net;
};

class Constructor : public Base {
  public:
    Identifier selector;
    std::deque<Identifier> arguments;
    Net net;
};

class SynPort : public Base {
  public:
    Identifier selector;
    std::deque<Identifier> variables;
    std::deque<Identifier> arguments;
    std::deque<PreCondPair> pre_conds;
    std::deque<CondPair> conds;
    std::optional<Guard> guard;
    std::deque<PostCondPair> post_conds;
};

class Class : public Base {
  public:
    Identifier name;
    Identifier base;
    std::optional<Net> object;
    std::deque<Method> methods;
    std::deque<Constructor> constructors;
    std::deque<SynPort> syn_ports;
};

class Classes : public Base {
  public:
    Identifier main;
    std::deque<Class> classes;
};

} // namespace AbstractSemanticGraph

namespace asg = AbstractSemanticGraph;
