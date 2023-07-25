#include "code.h"
#include "regex_constructor.h"
#include <iostream>

using namespace std;

CodeFiles::CodeFiles() {
}

CodeFiles::CodeFiles(const std::map<std::string, Code> &input_map) {
    if (input_map.find("") != input_map.end()) {
        free_code = input_map.find("")->second;
    }

    code_files.insert(input_map.begin(), input_map.end());
    code_files.erase("");
}

CodeFiles::CodeFiles(const std::map<std::string, Code> &input_map, const Code &_free_code) : free_code(_free_code) {
    code_files.insert(input_map.begin(), input_map.end());
}

// void CodeFiles::remove_slot(const std::string &slot_name) {
// }

void CodeFiles::apply(const std::map<std::string, CodeFiles> &replacements) {
    for (auto kv : replacements)
        apply(kv.first, kv.second);
}

void CodeFiles::apply(const std::string &key, const CodeFiles &replacement) {

    map<string, Code>::const_iterator file;
    bool free_code_used = false;

    for (std::map<std::string, Code>::iterator kv = code_files.begin(); kv != code_files.end(); kv++) {
        file = replacement.code_files.find(kv->first);

        if (file != replacement.code_files.end()) {
            /* uncommenting (optional replacements) and replacing corresponding code */
            kv->second.uncomment(key);
            kv->second.apply(key, file->second);
        } else {
            /* using free code */
            free_code_used = true;
            kv->second.uncomment(key);
            kv->second.apply(key, replacement.free_code);
        }
    }

    for (auto kv : replacement.code_files)
        if (code_files.find(kv.first) == code_files.end())
            code_files.insert(kv);

    if (!free_code_used) {
        free_code.uncomment(key);
        free_code.apply(key, replacement.free_code);
    }
}

void CodeFiles::apply(const std::string &slot_key, const std::string &slot_value) {
    apply({{slot_key, slot_value}});
}

void CodeFiles::apply(const std::map<std::string, std::string> &string_replacements) {
    std::map<std::string, Code> new_code_files;
    std::string filename;
    free_code = free_code.apply(string_replacements);

    for (auto kv : code_files) {
        filename = kv.first;
        for (auto replacement : string_replacements)
            filename = std::regex_replace(filename, regex_replacement(replacement.first), replacement.second);

        new_code_files.insert(std::pair<std::string, Code>(filename, kv.second.apply(string_replacements)));
    }

    code_files = new_code_files;
}

bool CodeFiles::contain_file(const std::string &filename) {
    return code_files.find(filename) != code_files.end();
}

void CodeFiles::print() {
    for (auto i : code_files) {
        std::cout << "File: " << i.first << "\n" << i.second.to_string() << std::endl;
    }
}
