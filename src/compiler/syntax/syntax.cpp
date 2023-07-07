#include "syntax.h"
#include "messages.h"
#include "return_values.h"
#include <cstdarg>

SyntaxAnalyzer::SyntaxAnalyzer() {
}

ast::Classes SyntaxAnalyzer::analyze(TokenStack &_tokenStack) {
    ast::Classes res;

    tokenStack = &_tokenStack;
    tokenStack->ptrHead();

    rule_classes(res);

    return res;
}

void SyntaxAnalyzer::next_token() {
    do {
        tokenStack->next();
    } while (tokenStack->curr()->isspace());
}

bool SyntaxAnalyzer::any_terminal_fun(const std::vector<TokenType> &types) {
    for (auto type : types)
        if (terminal(type))
            return true;

    return false;
}
bool SyntaxAnalyzer::terminal(TokenType type) {
    return tokenStack->curr()->type == type;
}

bool SyntaxAnalyzer::forward_check_fun(const std::vector<TokenType> &types) {
    std::vector<TokenType>::const_iterator type;
    Token *save = tokenStack->curr();
    type = types.begin();

    while (type != types.end() && terminal(*type)) {
        next_token();
        type++;
    }
    tokenStack->ptrSet(save);

    return type == types.end();
}
