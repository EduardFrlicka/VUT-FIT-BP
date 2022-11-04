#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#ifdef PROGRESS
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#define _ASCII_COLORS

#ifdef _ASCII_COLORS

#define ASCII_RED "\033[31m"
#define ASCII_BLACK "\033[30m"
#define ASCII_GREEN "\033[32m"
#define ASCII_YELLOW "\033[33m"
#define ASCII_BLUE "\033[34m"
#define ASCII_MAGENTA "\033[35m"
#define ASCII_CYAN "\033[36m"
#define ASCII_WHITE "\033[37m"
#define ASCII_RESET "\033[0m"

#define ASCII_BOLD "\033[01m"

#else

#define ASCII_RED
#define ASCII_BLACK
#define ASCII_GREEN
#define ASCII_YELLOW
#define ASCII_BLUE
#define ASCII_MAGENTA
#define ASCII_CYAN
#define ASCII_WHITE
#define ASCII_RESET

#define ASCII_BOLD

#endif

#define __ERROR(code, ...)                                                                                                                                                                             \
    do {                                                                                                                                                                                               \
        fprintf(stderr, "[" ASCII_BOLD ASCII_RED "  ERROR  " ASCII_RESET "] %s: ", __func__);                                                                                                          \
        fprintf(stderr, __VA_ARGS__);                                                                                                                                                                  \
        fprintf(stderr, "\n");                                                                                                                                                                         \
        return (code);                                                                                                                                                                                 \
    } while (0)

#ifndef LOG_LEVEL_ERROR
#define __WARNING(...)                                                                                                                                                                                 \
    do {                                                                                                                                                                                               \
        fprintf(stderr, "[" ASCII_BOLD ASCII_YELLOW " WARNING " ASCII_RESET "] %s: ", __func__);                                                                                                       \
        fprintf(stderr, __VA_ARGS__);                                                                                                                                                                  \
        fprintf(stderr, "\n");                                                                                                                                                                         \
    } while (0)

#ifndef LOG_LEVEL_WARNING
#define __DEBUG(...)                                                                                                                                                                                   \
    do {                                                                                                                                                                                               \
        fprintf(stderr, "[" ASCII_BOLD "  DEBUG  " ASCII_RESET "] %s: ", __func__);                                                                                                                    \
        fprintf(stderr, __VA_ARGS__);                                                                                                                                                                  \
        fprintf(stderr, "\n");                                                                                                                                                                         \
    } while (0)
#else
#define __DEBUG(...)
#endif
#else
#define __WARNING(...)
#define __DEBUG(...)
#endif

#define ERROR(code, ...) __ERROR(code, __VA_ARGS__);
#define WARNING(...) __WARNING(__VA_ARGS__);
#define DEBUG(...) __DEBUG(__VA_ARGS__);

#define NULLCHECK(ptr)                                                                                                                                                                                 \
    do {                                                                                                                                                                                               \
        if (!(ptr))                                                                                                                                                                                    \
            ERROR(ERR_INTERNAL, #ptr " is NULL");                                                                                                                                                      \
    } while (0)

#define ASSERT(expr)                                                                                                                                                                                   \
    do {                                                                                                                                                                                               \
        int res = (expr);                                                                                                                                                                              \
        if (res)                                                                                                                                                                                       \
            return res;                                                                                                                                                                                \
    } while (0)

#endif /* ERROR_H */
