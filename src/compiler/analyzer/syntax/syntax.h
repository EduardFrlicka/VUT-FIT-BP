#pragma once

#include "file.h"
#include "logger.h"
#include "syntax_tree.h"

class SyntaxAnalyzer {
  public:
    SyntaxAnalyzer(Logger &);

    int analyze_file(File *);

  private:
    File *file;
    Logger &logger;

    void next_token();

    int rule_classes(ast::Classes *);
    int rule_class(ast::Class *);
    int rule_classhead();
    int rule_objectnet();
    int rule_methodnet();
    int rule_constructor();
    int rule_sync();
    int rule_message();
    int rule_net();
    int rule_place();
    int rule_init();
    int rule_initmarking();
    int rule_initaction();
    int rule_transition();
    int rule_cond();
    int rule_precond();
    int rule_postcond();
    int rule_guard();
    int rule_action();
    int rule_arcexpr();
    int rule_miltiset();
    int rule_n();
    int rule_c();
    int rule_list();
    int rule_temps();
    int rule_unit();
    int rule_unaryexpr();
    int rule_primary();
    int rule_exprs();
    int rule_expr();
    int rule_expr2();
    int rule_expr3();
    int rule_keymsg();
    int rule_keysel();
    int rule_literal();
    int rule_arrayconst();
    int rule_array();
    int rule_number();
    int rule_string();
    int rule_charconst();
    int rule_symconst();
    int rule_symbol();
    int rule_id();
    int rule_selchar();
    int rule_hexDig();
    int rule_dig();
    int rule_letter();
    int rule_char();
};
