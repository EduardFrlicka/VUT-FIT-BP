#pragma once
#include "identifier.h"
#include "semantic_graph_base.h"
#include <deque>
#include <optional>

namespace AbstractSemanticGraph {

class Templ : public Base {};

class PreCondPair : public Base {};
class CondPair : public Base {};
class Guard : public Base {};
class Action : public Base {};
class PostCondPair : public Base {};

class Transition : public Base {};
class Place : public Base {
  public:
    Identifier name;
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
    std::deque<Identifier> arguments;
    std::deque<PreCondPair> pre_conds;
    std::deque<CondPair> conds;
    std::deque<Guard> guard;
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
