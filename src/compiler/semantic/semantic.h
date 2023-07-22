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

  private:
    int res;
    NameSpace classes;
    NameSpace variables;
    NameSpace messages;
    NameSpace places;
    NameSpace transitions;

    void analyze(const ast::Classes &);
    void analyze(const ast::Class &);
    void analyze(const ast::ClassHead &);
    void analyze(const ast::ObjectNet &);
    void analyze(const ast::MethodNet &);
    void analyze(const ast::Constructor &);
    void analyze(const ast::SynPort &);
    void analyze(const ast::Message &);
    void analyze(const ast::Net &);
    void analyze(const ast::Place &);
    void analyze(const ast::InitAction &);
    void analyze(const ast::Transition &);
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
