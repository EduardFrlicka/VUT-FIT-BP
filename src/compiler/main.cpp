#include "arguments.h"
#include "file.h"
#include "lexical.h"
#include "return_values.h"
#include <filesystem>
#include <stdio.h>
#include <string>
#include <vector>

void print_usage(char *binary);
void print_help(char *binary);
int playground(int argc, char *argv[]);

int main(int argc, char *argv[]) {

    // return playground(argc, argv);

    args = Arguments(argc, argv);

    if (args.help) {
        print_help(argv[0]);
        return SUCCESS;
    }

    auto lexxer = LexicalAnalyzer();

    TokenStack &tokenstack = lexxer.analyze(args.sources);

    return SUCCESS;
}

void print_usage(char *binary) {
    printf("For more help use: %s --help\n", binary);
}

void print_help(char *binary) {
    printf("Usage: %s [OPTIONS]\n", binary);
}
