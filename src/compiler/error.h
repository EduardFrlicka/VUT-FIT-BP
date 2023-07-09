#pragma once

#include "file_position.h"
#include "logger.h"
#include "return_values.h"
#include <filesystem>

#ifdef DEBUG_PRINT
#define internal_error(format, ...)                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        logger.c_error(FilePosition(__FILE__, __LINE__, 0), "Internal error occured: " format __VA_OPT__(, ) __VA_ARGS__);                                                                             \
        exit(ERR_INTERNAL);                                                                                                                                                                            \
    } while (0)
#else
#define internal_error(format, ...)                                                                                                                                                                    \
    do {                                                                                                                                                                                               \
        logger.c_error("Internal error occured: " format __VA_OPT__(, ) __VA_ARGS__);                                                                                                                  \
        exit(ERR_INTERNAL);                                                                                                                                                                            \
    } while (0)
#endif
