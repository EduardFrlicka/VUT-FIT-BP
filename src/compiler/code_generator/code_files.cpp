#include "code.h"
#include "regex_constructor.h"
#include <iostream>

using namespace std;

CodeFiles::CodeFiles(const std::map<std::string, Code> &input_map) {
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
    map<string, Code>::iterator file;

    for (auto kv : replacement.code_files) {
        file = code_files.find(kv.first);

        if (file != code_files.end()) {
            /* uncommenting (optional replacements) and replacing corresponding code */
            file->second.uncomment(key);
            file->second.replace(key, kv.second);
        } else {
            /* moving file to result */
            code_files.insert(make_pair(kv.first, kv.second));
        }
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
