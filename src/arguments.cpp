#include "arguments.h"

cArguments::cArguments(int argc, char *argv[]) {

    int opt;
    int longopt_idx;

    const char *shortopt = "h";

    const option longopt[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    while ((opt = getopt_long(argc, argv, shortopt, longopt, &longopt_idx)) != -1) {
        switch (opt) {
        case '?':
        case ':':
            break;

        case 'h':
            this->help = true;
            break;

        default:
            break;
        }
    }
}
