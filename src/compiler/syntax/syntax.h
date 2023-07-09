#pragma once

#include "expressions.h"
#include "file.h"
#include "logger.h"
#include "syntax_tree.h"

class SyntaxAnalyzer {
  public:
    SyntaxAnalyzer(TokenStackIterator &);

    ast::Classes &root();

  private:
    ast::Classes tree;
    TokenStackIterator &tokenStack;
    ExpressionSyntaxAnalyzer expressionAnalyzer;

    bool terminal(TokenType);
    bool any_terminal_fun(const std::vector<TokenType> &first);
    bool forward_check_fun(const std::vector<TokenType> &first);

    int rule_classes(ast::Classes &);
    int rule_class(ast::Class &);
    int rule_classhead(ast::ClassHead &);
    int rule_objectnet(ast::ObjectNet &);
    int rule_methodnet(ast::MethodNet &);
    int rule_constructor(ast::Constructor &);
    int rule_sync(ast::SynPort &);
    int rule_message(ast::Message &);
    int rule_net(ast::Net &);
    int rule_place(ast::Place &);
    int rule_init(ast::Init &);
    // int rule_initmarking();
    int rule_initaction(ast::InitAction &);
    int rule_transition(ast::Transition &);
    int rule_condition_pair(ast::ConditionPair &);
    int rule_cond(ast::Condition &);
    int rule_precond(ast::PreCondition &);
    int rule_postcond(ast::PostCondition &);
    int rule_guard(ast::Guard &);
    int rule_action(ast::Action &);
    // int rule_arcexpr();
    int rule_multiset(ast::MultiSet &);

    int rule_multiset_elem(ast::MultiSetElem &);
    int rule_multiset_term(ast::MultiSetTerm &);
    int rule_multiset_list(ast::MultiSetTerm::MultiSetList &);

    int rule_temps(std::vector<Token> &);
};
