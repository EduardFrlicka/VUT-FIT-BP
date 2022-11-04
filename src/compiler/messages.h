
#define __TOKEN_PLACE_FMT "%s:%u:%u:"
#define __TOKEN_PLACE_ARG token->filename, token->line, token->col

// #define __TOKEN_PLACE(text) __TOKEN_PLACE_FMT(text), __TOKEN_PLACE_ARG
#define __TOKEN_PLACE(text, ...) __TOKEN_PLACE_FMT text, __TOKEN_PLACE_ARG, ##__VA_ARGS__

#define MSG_SCCESS ""

#define MSG_TOKEN_STACK_EMPTY "Emty stack"
#define MSG_TOKEN_STACK_PTR_NULL "Stack pointer is NULL"

#define MSG_SYN_UNEXPECTED_TOKEN __TOKEN_PLACE("Unexpected token")
#define MSG_LEX_UNEXPECTED_CHAR __TOKEN_PLACE("Unexpected character")
#define MSG_LEX_UNEXPECTED_EOF __TOKEN_PLACE("Unexpected end of file")

