#include "error_printer.h"
#include "logger.h"
#include "template.h"
#include <iostream>
#include "regex_constructor.h"

using std::map;
using std::set;
using std::string;
using std::regex;
using std::smatch;
using namespace std::filesystem;

CodeTemplateManager::CodeTemplateManager(const std::filesystem::path &dir_path) {
    recursive_directory_iterator dir_contents(dir_path);
    string templ_name;
    CodeFiles templ;

    for (const directory_entry &file : dir_contents) {
        if (file.is_directory())
            continue;

        if (!file.is_regular_file()) {
            logger.c_warning(file.path(), "when parsing templates: unexpected file type, skipping file");
            continue;
        }

        if (file.path().extension() != ".t") {
            logger.c_warning(file.path(), "when parsing templates: unexpected file extension, skipping this file");
            continue;
        }

        templ_name = template_name(file.path(), dir_path);
        templ = create_template(file);

        templates.insert(std::make_pair(templ_name, templ));
    }
}

CodeFiles CodeTemplateManager::get(const std::string name) {
    auto it = templates.find(name);
    if (it == templates.end())
        internal_error("Missing template: %s", name.c_str());

    return (*it).second;
}

void CodeTemplateManager::initialize(const std::filesystem::path &dir_path) {
}

CodeFiles CodeTemplateManager::create_template(std::istream &stream) {
    std::map<std::string, Code> code_files;
    string line;
    string file_name;
    string file_code;

    regex empty_line(std::regex("^\\s*$"));
    regex file_selector(regex_special("file:(.*)"));
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
                code_files.insert(std::make_pair(file_name, Code(file_code)));

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
        code_files.insert(std::make_pair(file_name, Code(file_code)));
    return CodeFiles(code_files);
}

CodeFiles CodeTemplateManager::create_template(const std::filesystem::path &path) {
    std::ifstream file(path);
    return create_template(file);
}

path CodeTemplateManager::template_name(const std::filesystem::path &template_path, const std::filesystem::path &root_path) {
    path::iterator i;
    path tmp;

    for (i = template_path.begin(); i != template_path.end() && tmp != root_path; i++)
        tmp /= *i;

    if (tmp != root_path)
        internal_error("root path is not prefix of template path");

    tmp = path();

    for (; i != template_path.end(); i++)
        tmp /= *i;

    return tmp.replace_extension("");
}
