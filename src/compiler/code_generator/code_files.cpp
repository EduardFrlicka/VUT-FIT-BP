#include "code.h"
#include "regex_constructor.h"
#include <iostream>

using namespace std;

CodeFiles::CodeFiles(const std::map<std::string, Code> &input_map, const Code &_free_code) : free_code(_free_code) {
    code_files.insert(input_map.begin(), input_map.end());
}

CodeFiles CodeFiles::combine(const std::map<std::string, CodeFiles> &replacements) {
    CodeFiles res(*this);

    for (auto kv : replacements)
        res.replace(kv.first, kv.second);

    return res;
}

CodeFiles CodeFiles::combine(const std::string &key, const CodeFiles &replacement) {
    CodeFiles res(*this);
    res.replace(key, replacement);
    return res;
}

void CodeFiles::replace(const std::string &key, const CodeFiles &replacement) {
    map<string, Code>::const_iterator file;
    bool free_code_used = false;

    for (auto kv : code_files) {
        file = replacement.code_files.find(kv.first);

        if (file != replacement.code_files.end()) {
            /* uncommenting (optional replacements) and replacing corresponding code */
            kv.second.uncomment(key);
            kv.second.replace(key, file->second);
        } else {
            /* using free code */
            free_code_used = true;
            kv.second.uncomment(key);
            kv.second.replace(key, replacement.free_code);
        }
    }

    for (auto kv : replacement.code_files)
        if (code_files.find(kv.first) == code_files.end())
            code_files.insert(kv);

    if (!free_code_used) {
        free_code.uncomment(key);
        free_code.replace(key, replacement.free_code);
    }
}

bool CodeFiles::contain_file(const std::string &filename) {
    return code_files.find(filename) != code_files.end();
}

void CodeFiles::print() {
    for (auto i : code_files) {
        std::cout << "File: " << i.first << "\n" << i.second.to_string() << std::endl;
    }
}
