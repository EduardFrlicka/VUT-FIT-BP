#include "error.h"
#include "rule_frame.h"
#include "syntax.h"

#include <iostream>

int SyntaxAnalyzer::rule_classes(ast::Classes &node) {
    while (terminal(tokenClass))
        emplace_back_and_assert_rule(node.classes, rule_class);

    assert_terminal_succ(tokenMain);
    assert_and_save_identifier(node.main);

    while (terminal(tokenClass))
        emplace_back_and_assert_rule(node.classes, rule_class);

    assert_terminal(tokenEOF);
    return SUCCESS;
}

int SyntaxAnalyzer::rule_class(ast::Class &node) {
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

    return SUCCESS;
}

int SyntaxAnalyzer::rule_classhead(ast::ClassHead &node) {
    assert_and_save_identifier(node.derived);
    assert_terminal_succ(tokenIs_a);
    assert_and_save_identifier(node.base);
    return SUCCESS;
}

int SyntaxAnalyzer::rule_objectnet(ast::ObjectNet &node) {
    assert_terminal_succ(tokenObject);
    assert_rule(rule_net(node.net));
    return SUCCESS;
}

int SyntaxAnalyzer::rule_methodnet(ast::MethodNet &node) {
    assert_terminal_succ(tokenMethod);

    assert_rule(rule_message(node.message));
    assert_rule(rule_net(node.net));
    return SUCCESS;
}

int SyntaxAnalyzer::rule_constructor(ast::Constructor &node) {
    assert_terminal_succ(tokenConstructor);
    assert_rule(rule_message(node.message));
    assert_rule(rule_net(node.net));
    return SUCCESS;
}

int SyntaxAnalyzer::rule_sync(ast::SynPort &node) {
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

    return SUCCESS;
}

int SyntaxAnalyzer::rule_message(ast::Message &node) {
    if (any_terminal(tokenAdd, tokenSub, tokenIDiv, tokenMul, tokenEq, tokenNotEq, tokenEqIdentity, tokenNotEqIdentity, tokenLess, tokenGreater, tokenLessEq, tokenGreaterEq, tokenAnd, tokenOr,
                     tokenMod, tokenDiv, )) {
        node.binary.emplace();
        assert_and_save_identifier(node.binary->first);
        assert_and_save_identifier(node.binary->second);
        return SUCCESS;
    }

    if (!forward_check(tokenIdentifier, tokenColon, tokenIdentifier)) {
        assert_and_save_identifier(node.method);
        return SUCCESS;
    }

    while (forward_check(tokenIdentifier, tokenColon, tokenIdentifier)) {
        node.keys.emplace_back();
        assert_and_save_identifier(node.keys.rbegin()->first);
        assert_terminal_succ(tokenColon);
        assert_and_save_identifier(node.keys.rbegin()->second);
    }
    return SUCCESS;
}

int SyntaxAnalyzer::rule_net(ast::Net &node) {
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
    return SUCCESS;
}

int SyntaxAnalyzer::rule_place(ast::Place &node) {
    assert_terminal_succ(tokenPlace);
    assert_and_save_identifier(node.name);

    assert_terminal_succ(tokenLeftRoundBracket);
    if (!terminal(tokenRightRoundBracket))
        emplace_and_assert_rule(node.init_state, rule_multiset);
    assert_terminal_succ(tokenRightRoundBracket);

    if (terminal(tokenInit))
        emplace_and_assert_rule(node.init_func, rule_init);

    return SUCCESS;
}

int SyntaxAnalyzer::rule_init(ast::Init &node) {
    assert_terminal_succ(tokenInit);
    assert_terminal_succ(tokenLeftCurlyBracket);
    assert_rule(rule_initaction(node.action));
    assert_terminal_succ(tokenRightCurlyBracket);
    return SUCCESS;
}

int SyntaxAnalyzer::rule_initaction(ast::InitAction &node) {

    if (terminal(tokenOr))
        assert_rule(rule_temps(node.temporaries));

    assert_rule(expressionAnalyzer.analyze_expression(node.expr));

    return SUCCESS;
}

int SyntaxAnalyzer::rule_transition(ast::Transition &node) {
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

    return SUCCESS;
}

int SyntaxAnalyzer::rule_condition_pair(ast::ConditionPair &node) {
    assert_and_save_identifier(node.first);

    assert_terminal_succ(tokenLeftRoundBracket);
    assert_rule(rule_multiset(node.second));
    assert_terminal_succ(tokenRightRoundBracket);

    return SUCCESS;
}

int SyntaxAnalyzer::rule_cond(ast::Condition &node) {
    assert_terminal_succ(tokenCond);

    emplace_back_and_assert_rule(node.conditions, rule_condition_pair);

    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.conditions, rule_condition_pair);
    }

    return SUCCESS;
}

int SyntaxAnalyzer::rule_precond(ast::PreCondition &node) {
    assert_terminal_succ(tokenPrecond);

    emplace_back_and_assert_rule(node.conditions, rule_condition_pair);

    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.conditions, rule_condition_pair);
    }

    return SUCCESS;
}

int SyntaxAnalyzer::rule_postcond(ast::PostCondition &node) {
    assert_terminal_succ(tokenPostcond);

    emplace_back_and_assert_rule(node.conditions, rule_condition_pair);

    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.conditions, rule_condition_pair);
    }

    return SUCCESS;
}

int SyntaxAnalyzer::rule_guard(ast::Guard &node) {
    assert_terminal_succ(tokenGuard);

    assert_terminal_succ(tokenLeftCurlyBracket);
    assert_rule(expressionAnalyzer.analyze_expression(node.expr));
    assert_terminal_succ(tokenRightCurlyBracket);
    return SUCCESS;
}

int SyntaxAnalyzer::rule_action(ast::Action &node) {
    assert_terminal_succ(tokenAction);

    assert_terminal_succ(tokenLeftCurlyBracket);
    if (terminal(tokenOr))
        assert_rule(rule_temps(node.temporaries));
    assert_rule(expressionAnalyzer.analyze_expression(node.expr));
    assert_terminal_succ(tokenRightCurlyBracket);
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