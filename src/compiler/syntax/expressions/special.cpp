#include "expressions.h"
#include "expressions_tree.h"
#include "syntax_rule_frame.h"

int ExpressionSyntaxAnalyzer::code_block() {
    TokenStackIterator start;
    std::deque<Token> arguments;
    std::deque<Token> temporaries;
    ExpressionSyntaxAnalyzer expression_analyzer(tokenStack);
    ast::Expression expr;

    start = tokenStack;
    assert_terminal_succ(tokenLeftSquareBracket);

    while (terminal(tokenColon)) {
        assert_terminal_succ(tokenColon);
        assert_terminal(tokenIdentifier);
        arguments.push_back(tokenStack.get());
        tokenStack.succ();
    }

    if (!arguments.empty())
        assert_terminal_succ(tokenOr);

    expression_analyzer.analyze_expression(expr);
    stack.push(ast::Expression(ast::CodeBlock(arguments, temporaries, expr), start, tokenStack));

    assert_terminal_succ(tokenRightSquareBracket);

    return SUCCESS;
}

int ExpressionSyntaxAnalyzer::array_const() {
    TokenStackIterator start;
    std::deque<Token> values;

    assert_terminal_succ(tokenHash);
    assert_terminal_succ(tokenLeftRoundBracket);
    while (tokenStack.get().isliteral()) {
        values.push_back(tokenStack.get());
        tokenStack.succ();
    }
    stack.push(ast::Expression(ast::ConstArray(values), start, tokenStack));
    assert_terminal_succ(tokenRightRoundBracket);

    return 0;
}
