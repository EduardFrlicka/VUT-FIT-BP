#include "syntax.h"
#include "messages.h"
#include "return_values.h"
#include <cstdarg>

SyntaxAnalyzer::SyntaxAnalyzer(TokenStackIterator &_tokenStack) : tokenStack(_tokenStack), expressionAnalyzer(_tokenStack) {
    int res;

    if ((res = rule_classes(tree))) {
        tree.print();
        exit(res);
    }
}

ast::Classes &SyntaxAnalyzer::root() {
    return tree;
}

bool SyntaxAnalyzer::any_terminal_fun(const std::vector<TokenType> &types) {
    for (auto type : types)
        if (terminal(type))
            return true;

    return false;
}
bool SyntaxAnalyzer::terminal(TokenType type) {
    if (tokenStack.end())
        return false;
    return tokenStack.get().type == type;
}

bool SyntaxAnalyzer::forward_check_fun(const std::vector<TokenType> &types) {
    std::vector<TokenType>::const_iterator type;
    tokenStack.stash_push();
    type = types.begin();

    while (type != types.end() && terminal(*type)) {
        tokenStack.succ();
        type++;
    }
    tokenStack.stash_pop();

    return type == types.end();
}
