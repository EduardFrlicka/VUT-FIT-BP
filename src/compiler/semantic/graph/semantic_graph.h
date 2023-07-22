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

class ObjectNet : public Base {};

class Method : public Base {
    Identifier selector;
    std::deque<Identifier> arguments;
    ObjectNet net;
};

class Constructor : public Base {
    Identifier selector;
    std::deque<Identifier> arguments;
    ObjectNet net;
};

class SynPort : public Base {
    Identifier selector;
    std::deque<Identifier> arguments;
    std::deque<PreCondPair> pre_conds;
    std::deque<CondPair> conds;
    std::deque<Guard> guard;
    std::deque<PostCondPair> post_conds;
};

class Class : public Base {
    Identifier name;
    Identifier base;
    std::optional<ObjectNet> object;
};

class Classes : public Base {
    Identifier main;
    std::deque<Class> classes;
};

} // namespace AbstractSemanticGraph

namespace asg = AbstractSemanticGraph;
