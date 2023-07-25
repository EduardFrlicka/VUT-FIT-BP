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
    asg::Action analyze(const ast::InitAction &);
    asg::Transition analyze(const ast::Transition &);
    asg::CondPair analyze(const ast::ConditionPair &);
    std::deque<asg::CondPair> analyze(const ast::Condition &);
    std::deque<asg::PreCondPair> analyze(const ast::PreCondition &);
    std::deque<asg::PostCondPair> analyze(const ast::PostCondition &);
    asg::Guard analyze(const ast::Guard &);
    asg::Action analyze(const ast::Action &);

    asg::MultiSet analyze(const ast::MultiSet &);
    asg::MultiSetElemPair analyze(const ast::MultiSetElem &);
    asg::MultiSetTerm analyze(const ast::MultiSetTerm &);
    asg::MultiSetList analyze(const ast::MultiSetTerm::MultiSetList &);

    asg::Expression analyze(const ast::Expression &);
    asg::Expression analyze(const ast::ExpressionPair &);
    asg::Expression analyze(const ast::CascadeUnary &);
    asg::Expression analyze(const ast::CascadeBinary &);
    asg::Expression analyze(const ast::CascadeKeyWord &);
    asg::Expression analyze(const ast::ExpressionIdentifier &);
    asg::Expression analyze(const ast::ExpressionValue &);
    asg::Expression analyze(const ast::ExpressionUnary &);
    asg::Expression analyze(const ast::ExpressionBinary &);
    asg::Expression analyze(const ast::ExpressionKeyWord &);
    asg::Expression analyze(const ast::Assgiment &);
    asg::Expression analyze(const ast::Bracket &);
    asg::Expression analyze(const ast::CodeBlock &);
    asg::Expression analyze(const ast::ConstArray &);
};
