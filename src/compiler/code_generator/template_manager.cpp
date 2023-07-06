#include "logger.h"
#include "template.h"
#include <iostream>

using std::map;
using std::set;
using std::string;
using namespace std::filesystem;

CodeTemplateManager::CodeTemplateManager(const std::filesystem::path &dir_path) {
    initialize(dir_path);
}

CodeTemplateManager::CodeTemplateManager(string const &path_str) {
    path dir_path(path_str);
    initialize(dir_path);
}

CodeTemplateManager::CodeTemplateManager(const char *path_str) {
    path dir_path(path_str);
    initialize(dir_path);
}

CodeTemplate CodeTemplateManager::get(const std::string name) {
    std::map<std::string, CodeTemplate>::iterator res = raw_templates.find(name);
    if (res == raw_templates.end())
        throw std::invalid_argument("Unknown template: " + name);

    return (*res).second;
}

void CodeTemplateManager::initialize(const std::filesystem::path &dir_path) {
    recursive_directory_iterator dir_contents(dir_path);
    string templ_name;
    CodeTemplate templ;

    for (const directory_entry &file : dir_contents) {
        if (file.is_directory())
            continue;

        if (!file.is_regular_file()) {
            logger.note(file.path(), "when parsing templates: unexpected file type, skipping this file");
            continue;
        }

        if (file.path().extension() != ".t") {
            logger.note(file.path(), "when parsing templates: unexpected file extension, skipping this file");
            continue;
        }

        templ_name = template_name(file.path(), dir_path);
        templ = CodeTemplate(file);

        raw_templates.insert(std::pair<string, CodeTemplate>(templ_name, templ));
    }
}

path CodeTemplateManager::template_name(const std::filesystem::path &template_path, const std::filesystem::path &root_path) {
    path::iterator i;
    path tmp;

    for (i = template_path.begin(); i != template_path.end() && tmp != root_path; i++)
        tmp /= *i;

    if (tmp != root_path)
        throw std::invalid_argument("root path is not prefix of template path");

    tmp = path();

    for (; i != template_path.end(); i++)
        tmp /= *i;

    return tmp.replace_extension("");
}
