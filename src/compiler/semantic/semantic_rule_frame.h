#pragma once
#include "return_values.h"

#define analyze_vector(vector)                                                                                                                                                                         \
    do {                                                                                                                                                                                               \
        for (auto i : vector) {                                                                                                                                                                        \
            analyze(i);                                                                                                                                                                                \
        }                                                                                                                                                                                              \
    } while (0)

#define analyze_attribute(attribute)                                                                                                                                                                   \
    do {                                                                                                                                                                                               \
        analyze(attribute);                                                                                                                                                                            \
    } while (0)
