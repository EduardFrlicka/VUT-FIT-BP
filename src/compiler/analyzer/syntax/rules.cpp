#include "rule_frame.h"
#include "syntax.h"

int SyntaxAnalyzer::rule_classes(ast::Classes *node) {
    ast::Class *newClass = new ast::Class{};

    while (terminal(tokenClass)) {
        newClass = new ast::Class{};
        assert_non_terminal(rule_class(newClass));
        node->classes.push_back(newClass);
    }
    assert_terminal_succ(tokenMain);
    assert_terminal(tokenIdentifier);

    /* TODO AST */

    next_token();
    while (terminal(tokenClass)) {
        newClass = new ast::Class{};
        assert_non_terminal(rule_class(newClass));
        node->classes.push_back(newClass);
    }
    return 0;
}

int SyntaxAnalyzer::rule_class(ast::Class *node) {
    assert_terminal_succ(tokenClass);
    assert_non_terminal(rule_classhead());
    if (terminal(tokenObject))
        assert_non_terminal(rule_objectnet());

    while (terminal(tokenMethod) || terminal(tokenConstructor) || terminal(tokenSync)) {
        terminal_switch() {
        case tokenMethod:
            assert_non_terminal(rule_methodnet());
            break;

        case tokenConstructor:
            assert_non_terminal(rule_constructor());
            break;

        case tokenSync:
            assert_non_terminal(rule_sync());
            break;

        default:
            return ERR_SYNTAX;
        }
    }

    return 0;
}

int SyntaxAnalyzer::rule_classhead() {
    assert_terminal(tokenIdentifier);

    return 0;
}

int SyntaxAnalyzer::rule_objectnet() {
    return 0;
}

int SyntaxAnalyzer::rule_methodnet() {
    return 0;
}

int SyntaxAnalyzer::rule_constructor() {
    return 0;
}

int SyntaxAnalyzer::rule_sync() {
    return 0;
}

int SyntaxAnalyzer::rule_message() {
    return 0;
}

int SyntaxAnalyzer::rule_net() {
    return 0;
}

int SyntaxAnalyzer::rule_place() {
    return 0;
}

int SyntaxAnalyzer::rule_init() {
    return 0;
}

int SyntaxAnalyzer::rule_initmarking() {
    return 0;
}

int SyntaxAnalyzer::rule_initaction() {
    return 0;
}

int SyntaxAnalyzer::rule_transition() {
    return 0;
}

int SyntaxAnalyzer::rule_cond() {
    return 0;
}

int SyntaxAnalyzer::rule_precond() {
    return 0;
}

int SyntaxAnalyzer::rule_postcond() {
    return 0;
}

int SyntaxAnalyzer::rule_guard() {
    return 0;
}

int SyntaxAnalyzer::rule_action() {
    return 0;
}

int SyntaxAnalyzer::rule_arcexpr() {
    return 0;
}

int SyntaxAnalyzer::rule_miltiset() {
    return 0;
}

int SyntaxAnalyzer::rule_n() {
    return 0;
}

int SyntaxAnalyzer::rule_c() {
    return 0;
}

int SyntaxAnalyzer::rule_list() {
    return 0;
}

int SyntaxAnalyzer::rule_temps() {
    return 0;
}

int SyntaxAnalyzer::rule_unit() {
    return 0;
}

int SyntaxAnalyzer::rule_unaryexpr() {
    return 0;
}

int SyntaxAnalyzer::rule_primary() {
    return 0;
}

int SyntaxAnalyzer::rule_exprs() {
    return 0;
}

int SyntaxAnalyzer::rule_expr() {
    return 0;
}

int SyntaxAnalyzer::rule_expr2() {
    return 0;
}

int SyntaxAnalyzer::rule_expr3() {
    return 0;
}

int SyntaxAnalyzer::rule_keymsg() {
    return 0;
}

int SyntaxAnalyzer::rule_keysel() {
    return 0;
}

int SyntaxAnalyzer::rule_literal() {
    return 0;
}

int SyntaxAnalyzer::rule_arrayconst() {
    return 0;
}

int SyntaxAnalyzer::rule_array() {
    return 0;
}

int SyntaxAnalyzer::rule_number() {
    return 0;
}

int SyntaxAnalyzer::rule_string() {
    return 0;
}

int SyntaxAnalyzer::rule_charconst() {
    return 0;
}

int SyntaxAnalyzer::rule_symconst() {
    return 0;
}

int SyntaxAnalyzer::rule_symbol() {
    return 0;
}

int SyntaxAnalyzer::rule_id() {
    return 0;
}

int SyntaxAnalyzer::rule_selchar() {
    return 0;
}

int SyntaxAnalyzer::rule_hexDig() {
    return 0;
}

int SyntaxAnalyzer::rule_dig() {
    return 0;
}

int SyntaxAnalyzer::rule_letter() {
    return 0;
}

int SyntaxAnalyzer::rule_char() {
    return 0;
}
