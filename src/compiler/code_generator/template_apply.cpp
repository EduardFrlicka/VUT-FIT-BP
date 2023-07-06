#include "regex_constructor.h"
#include "template.h"

CodeFiles CodeTemplate::apply(const std::map<std::string, std::string> &string_replacements) {
    std::map<std::string, Code> new_code_files;

    for (auto kv : code_files) {
        new_code_files.insert(std::pair<std::string, Code>(replace(kv.first, string_replacements), kv.second.apply(string_replacements)));
        // new_code_files[] = ;
    }

    return CodeFiles(new_code_files);
}

std::string CodeTemplate::replace(const std::string &src, const std::map<std::string, std::string> &replacements) {

    std::string out(src);

    for (auto kv : replacements) {
        out = std::regex_replace(out, regex_replacement(kv.first), kv.second);
    }

    return out;
}
