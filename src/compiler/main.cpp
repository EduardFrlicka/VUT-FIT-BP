#include "arguments.h"
#include "lexical.h"
#include "return_values.h"
#include "syntax.h"
#include <stdio.h>

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

    auto lex_analyzer = LexicalAnalyzer();
    auto syn_analyzer = SyntaxAnalyzer();

    TokenStack &tokenstack = lex_analyzer.analyze(args.sources);

    auto syn_tree = syn_analyzer.analyze(tokenstack);

    syn_tree.print();

    return SUCCESS;
}

void print_usage(char *binary) {
    printf("For more help use: %s --help\n", binary);
}

void print_help(char *binary) {
    printf("Usage: %s [OPTIONS]\n", binary);
}
