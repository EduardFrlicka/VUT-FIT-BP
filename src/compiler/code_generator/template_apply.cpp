#include "regex_constructor.h"
#include "template.h"

CodeFiles CodeTemplate::apply(const std::map<std::string, std::string> &string_replacements) {
    std::map<std::string, Code> new_code_files;
    Code free_code;

    for (auto kv : code_files) {
        if (kv.first == std::string())
            free_code = kv.second.apply(string_replacements);
        else
            new_code_files.insert(std::pair<std::string, Code>(replace(kv.first, string_replacements), kv.second.apply(string_replacements)));
    }

    return CodeFiles(new_code_files, free_code);
}

std::string CodeTemplate::replace(const std::string &src, const std::map<std::string, std::string> &replacements) {

    std::string out(src);

    for (auto kv : replacements) {
        out = std::regex_replace(out, regex_replacement(kv.first), kv.second);
    }

    return out;
}
