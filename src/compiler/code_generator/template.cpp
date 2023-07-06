#include "template.h"
#include "regex_constructor.h"
#include "return_values.h"
#include <fstream>
#include <iostream>
#include <regex>

using std::map;
using std::set;
using std::string;
using namespace std;

typedef pair<string, Code> file_pair;

void CodeTemplate::initialize(std::istream &stream) {
    string line;
    string file_name;
    string file_code;

    regex empty_line(std::regex("^\\s*$"));
    regex file_selector(regex_special("file:(.+)"));
    regex ignore_line(regex_special("ignore"));
    regex no_newline(regex_special("inline"));
    regex newline(regex_special("newline"));

    smatch match;
    bool ignore = false;
    bool append_newline = true;

    while (std::getline(stream, line, '\n')) {
        if (regex_search(line, match, empty_line))
            continue;

        if (regex_search(line, match, file_selector)) {
            if (!file_code.empty())
                code_files.insert(file_pair(file_name, Code(file_code)));

            file_name = match[1];
            file_code.clear();
            continue;
        }

        if (regex_search(line, match, ignore_line)) {
            ignore = true;
            continue;
        }

        if (regex_search(line, match, no_newline)) {
            append_newline = false;
            continue;
        }

        if (regex_search(line, match, newline)) {
            file_code.append("\n");
            continue;
        }

        if (ignore) {
            ignore = false;
            continue;
        }

        file_code.append(line);

        if (append_newline)
            file_code.append("\n");
        else
            append_newline = true;
    }

    if (!file_code.empty())
        code_files.insert(file_pair(file_name, Code(file_code)));
}

CodeTemplate::CodeTemplate() {
}

CodeTemplate::CodeTemplate(const string &template_code) {
    istringstream stream(template_code);
    initialize(stream);
}

CodeTemplate::CodeTemplate(const std::filesystem::directory_entry &file) {
    ifstream stream(file.path());
    initialize(stream);
}

CodeTemplate::CodeTemplate(const std::filesystem::path &file_path) {
    ifstream stream(file_path);
    initialize(stream);
}

void CodeTemplate::print() {
    for (auto kv : code_files) {
        cout << kv.first << " :\n" << kv.second.to_string() << endl;
    }
}
