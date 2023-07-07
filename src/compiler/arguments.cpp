#include "arguments.h"
#include <getopt.h>

#define DEFAULT_TARGET_DIR "build"
#define DEFAULT_TARGET_BIN "binary"

Arguments args;

Arguments::Arguments(int argc, char *argv[]) {
    *this = Arguments();

    int opt;
    int longopt_idx;

    char **source;

    const char *shortopt = "ht";
    const option longopt[] = {
        {"help", no_argument, 0, 'h'}, {"target", required_argument, 0, 't'}, {"target_dir", required_argument, 0, 'd'}, {"conf_file", required_argument, 0, 'f'}, {0, 0, 0, 0},
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

    for (source = argv + optind; *source; source++) {
        sources.push_back(std::string(*source));
    }
    
}

Arguments::Arguments() {
}
