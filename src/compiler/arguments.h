#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "error.h"
#include <getopt.h>

class cArguments {
  public:
    char *target_dir = "build";
    char *target_bin = "binary";

    char **sources = nullptr;

    bool help = false;

    cArguments(int argc, char *argv[]);
};

#endif /* ARGUMENTS_H */
