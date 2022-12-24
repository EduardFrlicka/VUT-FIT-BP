#include "arguments.h"
#include "file.h"
#include "lexical.h"
#include "return_values.h"
#include <filesystem>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

#include "template.h"

void print_usage(char *binary);
void print_help(char *binary);
int process_path(std::vector<File *> &input_files, std::filesystem::path path);

int main(int argc, char *argv[]) {

    cArguments args = cArguments(argc, argv);

    // if (args.help) {
    //     print_help(argv[0]);
    //     return SUCCESS;
    // }

    // std::vector<File *> input_files;

    // for (char **source = args.sources; *source; source++) {
    //     File *newFile = new File(*source);
    //     ASSERT(newFile->init());
    //     input_files.push_back(newFile);
    //     // ASSERT(process_path(input_files, *source));

    //     // File file = File(*source);
    //     // ASSERT(file.init());
    //     // lex_analyze_file(&file);
    // }

    // auto logger = Logger();
    // auto lexxer = LexicalAnalyzer(logger);
    // for (auto file : input_files) {
    //     lexxer.analyze_file(file);
    //     file->tokenStack.printStack();
    // }

    CodeTemplate templ("class __name__ {\n"
                       "  private:\n"
                       "    /* __data__ */\n"
                       "    /* __data_opt__ */\n"
                       "  public:\n"
                       "    __name__(/* args */);\n"
                       "    ~__name__();\n"
                       "};\n"
                       "\n"
                       "__name__::__name__(/* args */) {\n"
                       "}\n"
                       "\n"
                       "__name__::~__name__() {\n"
                       "}\n");

    std::map<std::string, std::string> map = {{"name", "Name"}, {"data", "int s;"}};
    std::map<std::string, std::string> map2 = {{"name", "Name2"}};

    printf("%s", templ.apply(map).c_str());
    printf("%s", templ.apply(map2).c_str());

    return SUCCESS;
}

void print_usage(char *binary) {
    printf("For more help use: %s --help\n", binary);
}

void print_help(char *binary) {
    printf("Usage: %s [OPTIONS]\n", binary);
}

int process_path(std::vector<File *> &input_files, std::filesystem::path path) {
    using namespace std::filesystem;
    DEBUG("processing %s", path.c_str());
    switch (status(path).type()) {
    case file_type::directory:
        /* https://en.cppreference.com/w/cpp/filesystem/is_directory */
        for (auto it = directory_iterator(path); it != directory_iterator(); ++it) {
            ASSERT(process_path(input_files, *it));
        }
        break;

    case file_type::symlink:
        DEBUG("symlink");
        ASSERT(process_path(input_files, read_symlink(path)));
        break;

    case file_type::regular: {
        const char *path_str = path.c_str();
        File *newFile = new File(path_str);
        ASSERT(newFile->init());
        input_files.push_back(newFile);
        break;
    }

    case file_type::not_found:
        WARNING("file does not exist: %s", path.c_str());
        break;

    default:
        return ERR_FILE;
    }
    return SUCCESS;
}
