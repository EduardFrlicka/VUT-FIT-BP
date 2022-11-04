#include "arguments.h"


#define DEFAULT_TARGET_DIR "build"
#define DEFAULT_TARGET_BIN "binary"

cArguments::cArguments(int argc, char *argv[]) {

    int opt;
    int longopt_idx;

    const char *shortopt = "ht";

    const option longopt[] = {
        {"help", no_argument, 0, 'h'},
        {"target", required_argument, 0, 't'},
        {"target_dir", required_argument, 0, 'd'},
        {"conf_file", required_argument, 0, 'f'},
        {0, 0, 0, 0},
    };



    while ((opt = getopt_long(argc, argv, shortopt, longopt, &longopt_idx)) != -1) {
        switch (opt) {
        case '?':
        case ':':
            break;

        case 'h':
            DEBUG("help option");
            this->help = true;
            break;

        default:
            break;
        }
    }

    this->sources = argv + optind;

}
