#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <getopt.h>
#include "error.h"


class cArguments {
  public:
    char *target_dir;
    char *target_bin;

    bool help;

    cArguments(int argc, char *argv[]);
};


#endif /* ARGUMENTS_H */
