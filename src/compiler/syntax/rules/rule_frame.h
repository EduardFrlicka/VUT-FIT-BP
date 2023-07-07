#include "file.h"
#include "logger.h"
#include "messages.h"
#include "return_values.h"
#include "token.h"

// File *file;
// Logger logger;

#define RULE(...)                                                                                                                                                                                      \
    do {                                                                                                                                                                                               \
        int rule_res;                                                                                                                                                                                  \
        for (auto func : [__VA_ARGS__])                                                                                                                                                                \
    } while (0)

#define current_token *(tokenStack->curr())

#define any_terminal(...) any_terminal_fun({__VA_ARGS__})
#define forward_check(...) forward_check_fun({__VA_ARGS__})

#define terminal_switch() switch (tokenStack->curr()->type)

#define assert_terminal(token_type)                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        Token *token = tokenStack->curr();                                                                                                                                                             \
        if (token->type != (token_type)) {                                                                                                                                                             \
            logger.error(*token, MSG_SYN_UNEXPECTED_TOKEN_EXPECTED, token->type_string().c_str(), Token::type_string(token_type).c_str());                                                             \
            return ERR_SYNTAX;                                                                                                                                                                         \
        }                                                                                                                                                                                              \
    } while (0)

#define assert_terminal_succ(token_type)                                                                                                                                                               \
    do {                                                                                                                                                                                               \
        assert_terminal(token_type);                                                                                                                                                                   \
        next_token();                                                                                                                                                                                  \
    } while (0)

#define assert_rule(rule_func)                                                                                                                                                                         \
    do {                                                                                                                                                                                               \
        int res = (rule_func);                                                                                                                                                                         \
        if (res) {                                                                                                                                                                                     \
            return res;                                                                                                                                                                                \
        }                                                                                                                                                                                              \
    } while (0)

#define emplace_and_assert_rule(optional, rule_func)                                                                                                                                                   \
    do {                                                                                                                                                                                               \
        (optional).emplace();                                                                                                                                                                          \
        assert_rule(rule_func(*(optional)));                                                                                                                                                           \
    } while (0);

#define emplace_back_and_assert_rule(vector, rule_func)                                                                                                                                                \
    do {                                                                                                                                                                                               \
        (vector).emplace_back();                                                                                                                                                                       \
        assert_rule(rule_func(*(vector).rbegin()));                                                                                                                                                    \
    } while (0);

#define assert_and_save_identifier(dest)                                                                                                                                                               \
    do {                                                                                                                                                                                               \
        assert_terminal(tokenIdentifier);                                                                                                                                                              \
        (dest) = *(tokenStack->curr());                                                                                                                                                                  \
        next_token();                                                                                                                                                                                  \
    } while (0)
