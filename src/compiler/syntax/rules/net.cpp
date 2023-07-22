#include "error.h"
#include "syntax.h"
#include "syntax_rule_frame.h"

#include <iostream>

int SyntaxAnalyzer::rule_classes(ast::Classes &node) {
    node.begin = tokenStack.get().it;
    while (terminal(tokenClass))
        emplace_back_and_assert_rule(node.classes, rule_class);

    assert_terminal_succ(tokenMain);
    assert_and_save_identifier(node.main);

    while (terminal(tokenClass))
        emplace_back_and_assert_rule(node.classes, rule_class);

    node.end = tokenStack.get(-1).it;
    assert_terminal(tokenEOF);
    return SUCCESS;
}

int SyntaxAnalyzer::rule_class(ast::Class &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenClass);
    assert_rule(rule_classhead(node.head));

    if (terminal(tokenObject)) {
        emplace_and_assert_rule(node.object, rule_objectnet)
    }
    assert_terminal_neg(tokenObject);

    while (any_terminal(tokenMethod, tokenConstructor, tokenSync)) {
        terminal_switch() {
        case tokenMethod:
            emplace_back_and_assert_rule(node.methods, rule_methodnet);
            break;

        case tokenConstructor:
            emplace_back_and_assert_rule(node.constructors, rule_constructor);
            break;

        case tokenSync:
            emplace_back_and_assert_rule(node.syn_ports, rule_sync);
            break;

        default:
            return ERR_SYNTAX;
        }
    }

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_classhead(ast::ClassHead &node) {
    node.begin = tokenStack.get().it;
    assert_and_save_identifier(node.derived);
    assert_terminal_succ(tokenIs_a);
    assert_and_save_identifier(node.base);
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_objectnet(ast::ObjectNet &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenObject);
    assert_rule(rule_net(node.net));
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_methodnet(ast::MethodNet &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenMethod);

    assert_rule(rule_message(node.message));
    assert_rule(rule_net(node.net));
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_constructor(ast::Constructor &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenConstructor);
    assert_rule(rule_message(node.message));
    assert_rule(rule_net(node.net));
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_sync(ast::SynPort &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenSync);
    assert_rule(rule_message(node.message));

    if (terminal(tokenCond))
        emplace_and_assert_rule(node.conditions, rule_cond);
    assert_terminal_neg(tokenCond);

    if (terminal(tokenPrecond))
        emplace_and_assert_rule(node.pre_conditions, rule_precond);
    assert_terminal_neg(tokenPrecond);

    if (terminal(tokenGuard))
        emplace_and_assert_rule(node.guard, rule_guard);
    assert_terminal_neg(tokenGuard);

    if (terminal(tokenPostcond))
        emplace_and_assert_rule(node.post_contitions, rule_postcond);
    assert_terminal_neg(tokenPostcond);

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_message(ast::Message &node) {
    node.begin = tokenStack.get().it;
    if (any_terminal(tokenAdd, tokenSub, tokenIDiv, tokenMul, tokenEq, tokenNotEq, tokenEqIdentity, tokenNotEqIdentity, tokenLess, tokenGreater, tokenLessEq, tokenGreaterEq, tokenAnd, tokenOr,
                     tokenMod, tokenDiv, )) {
        node.binary.emplace();
        assert_and_save_identifier(node.binary->first);
        assert_and_save_identifier(node.binary->second);
        node.end = tokenStack.get(-1).it;
        return SUCCESS;
    }

    if (!forward_check(tokenIdentifier, tokenColon, tokenIdentifier)) {
        assert_and_save_identifier(node.unary);
        node.end = tokenStack.get(-1).it;
        return SUCCESS;
    }

    while (forward_check(tokenIdentifier, tokenColon, tokenIdentifier)) {
        node.keys.emplace_back();
        assert_and_save_identifier(node.keys.rbegin()->first);
        assert_terminal_succ(tokenColon);
        assert_and_save_identifier(node.keys.rbegin()->second);
    }
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_net(ast::Net &node) {
    node.begin = tokenStack.get().it;
    while (any_terminal(tokenPlace, tokenTrans)) {
        terminal_switch() {
        case tokenPlace:
            emplace_back_and_assert_rule(node.places, rule_place);
            break;
        case tokenTrans:
            emplace_back_and_assert_rule(node.transitions, rule_transition);
            break;
        default:
            break;
        }
    }
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_place(ast::Place &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenPlace);
    assert_and_save_identifier(node.name);

    assert_terminal_succ(tokenLeftRoundBracket);
    if (!terminal(tokenRightRoundBracket))
        emplace_and_assert_rule(node.init_state, rule_multiset);
    assert_terminal_succ(tokenRightRoundBracket);

    if (terminal(tokenInit))
        emplace_and_assert_rule(node.init_func, rule_initaction);

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_initaction(ast::InitAction &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenInit);
    assert_terminal_succ(tokenLeftCurlyBracket);

    if (terminal(tokenOr))
        assert_rule(rule_temps(node.temporaries));

    assert_rule(expressionAnalyzer.analyze_expression(node.expr));

    assert_terminal_succ(tokenRightCurlyBracket);
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_transition(ast::Transition &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenTrans);
    assert_and_save_identifier(node.name);

    if (terminal(tokenCond))
        emplace_and_assert_rule(node.conditions, rule_cond);
    assert_terminal_neg(tokenCond);

    if (terminal(tokenPrecond))
        emplace_and_assert_rule(node.pre_conditions, rule_precond);
    assert_terminal_neg(tokenPrecond);

    if (terminal(tokenGuard))
        emplace_and_assert_rule(node.guard, rule_guard);
    assert_terminal_neg(tokenGuard);

    if (terminal(tokenAction))
        emplace_and_assert_rule(node.action, rule_action);
    assert_terminal_neg(tokenAction);

    if (terminal(tokenPostcond))
        emplace_and_assert_rule(node.post_contitions, rule_postcond);
    assert_terminal_neg(tokenPostcond);

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_condition_pair(ast::ConditionPair &node) {
    node.begin = tokenStack.get().it;
    assert_and_save_identifier(node.first);

    assert_terminal_succ(tokenLeftRoundBracket);
    assert_rule(rule_multiset(node.second));
    assert_terminal_succ(tokenRightRoundBracket);

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_cond(ast::Condition &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenCond);

    emplace_back_and_assert_rule(node.conditions, rule_condition_pair);

    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.conditions, rule_condition_pair);
    }

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_precond(ast::PreCondition &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenPrecond);

    emplace_back_and_assert_rule(node.conditions, rule_condition_pair);

    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.conditions, rule_condition_pair);
    }

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_postcond(ast::PostCondition &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenPostcond);

    emplace_back_and_assert_rule(node.conditions, rule_condition_pair);

    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.conditions, rule_condition_pair);
    }

    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_guard(ast::Guard &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenGuard);

    assert_terminal_succ(tokenLeftCurlyBracket);
    assert_rule(expressionAnalyzer.analyze_expression(node.expr));
    assert_terminal_succ(tokenRightCurlyBracket);
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_action(ast::Action &node) {
    node.begin = tokenStack.get().it;
    assert_terminal_succ(tokenAction);

    assert_terminal_succ(tokenLeftCurlyBracket);
    if (terminal(tokenOr))
        assert_rule(rule_temps(node.temporaries));
    assert_rule(expressionAnalyzer.analyze_expression(node.expr));
    assert_terminal_succ(tokenRightCurlyBracket);
    node.end = tokenStack.get(-1).it;
    return SUCCESS;
}

int SyntaxAnalyzer::rule_temps(std::vector<Token> &array) {
    assert_terminal_succ(tokenOr);

    while (terminal(tokenIdentifier)) {
        array.push_back(tokenStack.get());
        assert_terminal_succ(tokenIdentifier);
    }

    assert_terminal_succ(tokenOr);
    return SUCCESS;
}