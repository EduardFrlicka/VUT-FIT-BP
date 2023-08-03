#include "arguments.h"
#include "generator.h"
#include "lexical.h"
#include "return_values.h"
#include "semantic.h"
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

    auto lex_analyzer = LexicalAnalyzer(args.sources);

    auto syn_analyzer = SyntaxAnalyzer(lex_analyzer.begin());

    // syn_analyzer.root().print();

    auto sem_analyzer = SemanticAnalyzer(syn_analyzer.root());

    auto code_generator = CodeGenerator(sem_analyzer.root());

    code_generator.writeFiles();

    return SUCCESS;
}

void print_usage(char *binary) {
    printf("For more help use: %s --help\n", binary);
}

void print_help(char *binary) {
    printf("Usage: %s [OPTIONS]\n", binary);
}
