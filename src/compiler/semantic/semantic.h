#pragma once
#include "identifier.h"
#include "semantic_graph.h"
#include "syntax_tree.h"
#include <deque>
#include <map>
#include <vector>

class NameSpace {
  private:
    std::deque<std::map<std::string, Identifier>> stack;
    Identifier dummy;

  public:
    NameSpace();

    bool search(const Identifier &);
    bool search(const BasicIdentifier &);
    bool search(const std::string &);

    Identifier &get(const Identifier &);
    Identifier &get(const BasicIdentifier &);
    Identifier &get(const std::string &);

    void push(const Identifier &);
    void push_frame();
    void pop_frame();
};

class SemanticAnalyzer {
  public:
    SemanticAnalyzer(const ast::Classes &);
    asg::Classes &root();

  private:
    int res = 0;
    asg::Classes _root;
    NameSpace classes;
    NameSpace variables;
    NameSpace messages;
    NameSpace places;
    NameSpace transitions;

    asg::Classes analyze(const ast::Classes &);
    asg::Class analyze(const ast::Class &);
    void analyze(const ast::ClassHead &);
    asg::Net analyze(const ast::ObjectNet &);
    asg::Method analyze(const ast::MethodNet &);
    asg::Constructor analyze(const ast::Constructor &);
    asg::SynPort analyze(const ast::SynPort &);
    std::pair<Identifier, std::deque<Identifier>> analyze(const ast::Message &);
    asg::Net analyze(const ast::Net &);
    asg::Place analyze(const ast::Place &);
    void analyze(const ast::InitAction &);
    asg::Transition analyze(const ast::Transition &);
    void analyze(const ast::ConditionPair &);
    void analyze(const ast::Condition &);
    void analyze(const ast::PreCondition &);
    void analyze(const ast::PostCondition &);
    void analyze(const ast::Guard &);
    void analyze(const ast::Action &);
    void analyze(const ast::MultiSet &);
    void analyze(const ast::MultiSetElem &);
    void analyze(const ast::MultiSetTerm &);
    void analyze(const ast::MultiSetTerm::MultiSetList &);

    void analyze(const ast::Expression &);
    void analyze(const ast::ExpressionPair &);
    void analyze(const ast::CascadeUnary &);
    void analyze(const ast::CascadeBinary &);
    void analyze(const ast::CascadeKeyWord &);
    void analyze(const ast::ExpressionIdentifier &);
    void analyze(const ast::ExpressionValue &);
    void analyze(const ast::ExpressionUnary &);
    void analyze(const ast::ExpressionBinary &);
    void analyze(const ast::ExpressionKeyWord &);
    void analyze(const ast::Assgiment &);
};
