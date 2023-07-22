#include "syntax.h"
#include "syntax_rule_frame.h"
#include <iostream>

int SyntaxAnalyzer::rule_multiset(ast::MultiSet &node) {
    emplace_back_and_assert_rule(node.elements, rule_multiset_elem);

    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.elements, rule_multiset_elem);
    }

    return SUCCESS;
}

int SyntaxAnalyzer::rule_multiset_elem(ast::MultiSetElem &node) {
    if (forward_check(tokenInteger, tokenBacktick) || forward_check(tokenIdentifier, tokenBacktick)) {
        node.count = current_token;
        tokenStack.succ(); /* skipping ( number | identifier )*/
        assert_terminal_succ(tokenBacktick);
    }
    assert_rule(rule_multiset_term(node.term));
    return SUCCESS;
}

int SyntaxAnalyzer::rule_multiset_term(ast::MultiSetTerm &node) {
    if (terminal(tokenLeftRoundBracket)) {
        emplace_and_assert_rule(node.list, rule_multiset_list);
        return SUCCESS;
    }

    if (!terminal(tokenIdentifier) && !tokenStack.get().isliteral())
        assert_terminal(tokenIdentifier); /* asserting one of checked, to raise error */

    node.value = current_token;
    tokenStack.succ();

    return SUCCESS;
}

int SyntaxAnalyzer::rule_multiset_list(ast::MultiSetTerm::MultiSetList &node) {
    assert_terminal_succ(tokenLeftRoundBracket);

    emplace_back_and_assert_rule(node.values, rule_multiset_term);
    while (terminal(tokenComma)) {
        assert_terminal_succ(tokenComma);
        emplace_back_and_assert_rule(node.values, rule_multiset_term);
    };

    if (forward_check(tokenOr, tokenLeftRoundBracket)) {
        assert_terminal_succ(tokenOr);
        assert_rule(rule_multiset_list(node));
        assert_terminal_succ(tokenRightRoundBracket);
        return SUCCESS;
    }

    if (terminal(tokenOr)) {
        assert_terminal_succ(tokenOr);
        assert_and_save_identifier(node.tail);
    }
    assert_terminal_succ(tokenRightRoundBracket);

    return SUCCESS;
}
