#include "arguments.h"
#include <stdio.h>

void print_usage(char *binary);
void print_help(char *binary);

int main(int argc, char *argv[]) {

    cArguments args = cArguments(argc, argv);

    if (args.help) {
        print_help(argv[0]);
        return SUCCESS;
    }

    return SUCCESS;
}

void print_usage(char *binary) {
    printf("For more help use: %s --help\n", binary);
}

void print_help(char *binary) {
    printf("Usage: %s [OPTIONS]\n", binary);
}
