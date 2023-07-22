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

#define current_token tokenStack.get()

#define any_terminal(...) any_terminal_fun({__VA_ARGS__})
#define forward_check(...) forward_check_fun({__VA_ARGS__})

#define terminal_switch() switch (tokenStack.get().type)

#define assert_terminal_neg(token_type)                                                                                                                                                                \
    do {                                                                                                                                                                                               \
        if (terminal(token_type)) {                                                                                                                                                                    \
            logger.c_error(tokenStack.get(), MSG_SYN_UNEXPECTED_TOKEN_EXPECTED, tokenStack.get().type_string().c_str(), Token::type_string(token_type).c_str());                                       \
            return ERR_SYNTAX;                                                                                                                                                                         \
        }                                                                                                                                                                                              \
    } while (0)

#define assert_terminal(token_type)                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        if (!terminal(token_type)) {                                                                                                                                                                   \
            if (tokenStack.end())                                                                                                                                                                      \
                logger.c_error(MSG_LEX_UNEXPECTED_EOF);                                                                                                                                                \
            else                                                                                                                                                                                       \
                logger.c_error(tokenStack.get(), MSG_SYN_UNEXPECTED_TOKEN_EXPECTED, tokenStack.get().type_string().c_str(), Token::type_string(token_type).c_str());                                   \
            return ERR_SYNTAX;                                                                                                                                                                         \
        }                                                                                                                                                                                              \
    } while (0)

#define assert_terminal_succ(token_type)                                                                                                                                                               \
    do {                                                                                                                                                                                               \
        assert_terminal(token_type);                                                                                                                                                                   \
        if (!tokenStack.end())                                                                                                                                                                         \
            tokenStack.succ();                                                                                                                                                                         \
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
        (dest) = tokenStack.get();                                                                                                                                                                     \
        tokenStack.succ();                                                                                                                                                                             \
    } while (0)
