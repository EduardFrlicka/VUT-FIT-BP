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

#define terminal(token_type) (file->tokenStack.curr()->type == (token_type))

#define terminal_switch() switch (file->tokenStack.curr()->type)

#define assert_terminal(token_type)                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        Token *token = file->tokenStack.curr();                                                                                                                                                        \
        if (token->type != (token_type)) {                                                                                                                                                             \
            logger.error_at(*token, MSG_SYN_UNEXPECTED_TOKEN_EXPECTED, token->type_string().c_str(), Token::type_string(token_type).c_str());                                                                  \
            return ERR_SYNTAX;                                                                                                                                                                         \
        }                                                                                                                                                                                              \
    } while (0)

#define assert_terminal_succ(token_type)                                                                                                                                                               \
    do {                                                                                                                                                                                               \
        assert_terminal(token_type);                                                                                                                                                                   \
        next_token();                                                                                                                                                                                  \
    } while (0)

#define assert_non_terminal(rule_func)                                                                                                                                                                 \
    do {                                                                                                                                                                                               \
        int res = (rule_func);                                                                                                                                                                         \
        if (res) {                                                                                                                                                                                     \
            return res;                                                                                                                                                                                \
        }                                                                                                                                                                                              \
    } while (0)
