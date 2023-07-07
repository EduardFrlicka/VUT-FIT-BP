#include "rule_frame.h"
#include "syntax.h"

#include <iostream>

int SyntaxAnalyzer::rule_classes(ast::Classes &node) {
    ast::Class new_class;

    while (terminal(tokenClass)) {
        assert_rule(rule_class(new_class));
        node.classes.push_back(new_class);
        new_class.~Class();
    }

    assert_terminal_succ(tokenMain);
    assert_terminal(tokenIdentifier);
    node.main = current_token;
    next_token();

    while (terminal(tokenClass)) {
        assert_rule(rule_class(new_class));
        node.classes.push_back(new_class);
        new_class.~Class();
    }

    return SUCCESS;
}

int SyntaxAnalyzer::rule_class(ast::Class &node) {
    assert_terminal_succ(tokenClass);
    assert_rule(rule_classhead(node.head));

    if (terminal(tokenObject)) {
        emplace_and_assert_rule(node.object, rule_objectnet)
    }

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

    if (forward_check(tokenIdentifier, tokenIdentifier)) {
        while (forward_check(tokenIdentifier, tokenIdentifier)) {
            node.keys.emplace_back();
            assert_and_save_identifier(node.keys.rbegin()->first);
            assert_and_save_identifier(node.keys.rbegin()->second);
        }
        return SUCCESS;
    }

    assert_and_save_identifier(node.method);
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
    /*TODO*/
    return SUCCESS;
}

int SyntaxAnalyzer::rule_transition(ast::Transition &node) {
    assert_terminal_succ(tokenTrans);
    assert_and_save_identifier(node.name);

    if (terminal(tokenCond))
        emplace_and_assert_rule(node.conditions, rule_cond);
    if (terminal(tokenPrecond))
        emplace_and_assert_rule(node.pre_conditions, rule_precond);
    if (terminal(tokenGuard))
        emplace_and_assert_rule(node.guard, rule_guard);
    if (terminal(tokenAction))
        emplace_and_assert_rule(node.action, rule_action);
    if (terminal(tokenPostcond))
        emplace_and_assert_rule(node.post_contitions, rule_postcond);

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
    return SUCCESS;
    assert_terminal_succ(tokenGuard);

    assert_terminal_succ(tokenLeftCurlyBracket);
    /*TODO*/
    assert_terminal_succ(tokenRightCurlyBracket);
    return SUCCESS;
}

int SyntaxAnalyzer::rule_action(ast::Action &node) {
    return SUCCESS;
    assert_terminal_succ(tokenAction);

    assert_terminal_succ(tokenLeftCurlyBracket);
    /*TODO*/
    assert_terminal_succ(tokenRightCurlyBracket);
    return SUCCESS;
}
