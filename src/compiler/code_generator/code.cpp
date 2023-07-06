#include "code.h"
#include "regex_constructor.h"
#include <iostream>
#include <regex>
#include <sstream>
// #include <stdio.h>

using namespace std;

Code::Code(const string &_code) {
    include = set<string>();
    string tmp(_code);

    regex include_regex("#include\\s+((<[^>]+>)|(\"[^\"]+\"))\n?");
    sregex_iterator i;

    for (i = sregex_iterator(tmp.begin(), tmp.end(), include_regex); i != sregex_iterator(); i++)
        include.insert((*i)[1].str());

    code = regex_replace(tmp, include_regex, "");
}

Code::Code(const string &_code, const set<string> &_include = {}) : code(_code), include(_include) {
}

void Code::replace(regex key, string value) {
    std::string out;
    std::map<std::string, std::string> changes;

    for (std::string in : include) {
        out = regex_replace(in, key, value);
        if (out != in)
            changes[in] = out;
    }

    for (auto change : changes) {
        include.erase(change.first);
        include.insert(change.second);
    }

    code = regex_replace(code, key, value);
}

void Code::replace(std::string key, Code value) {
    include.merge(value.include);
    code = regex_replace(code, regex_replacement(key), value.code);
}

void Code::replace(regex key, Code value) {
    include.merge(value.include);
    code = regex_replace(code, key, value.code);
}

void Code::replace(std::string key, std::string value) {
    replace(regex_replacement(key), value);
}

void Code::uncomment(const std::string &key) {
    regex re = regex_optional("(.*?__" + key + "__.*?\n?)");
    replace(re, "$1");
}

Code Code::apply(std::map<std::string, std::string> replacements) {
    Code out(code, include);

    for (auto kv : replacements) {
        out.uncomment(kv.first);
        out.replace(kv.first, kv.second);
    }

    return out;
}

void Code::append(Code to_append) {
    include.merge(to_append.include);
    code.append(to_append.code);
}

void Code::append(std::vector<Code> to_append_vector) {
    for (Code to_append : to_append_vector) {
        include.merge(to_append.include);
        code.append(to_append.code);
    }
}

string Code::to_string() {
    string res = "";
    for (string header : include) {
        res += "#include " + header + "\n";
    }
    if (!res.empty())
        res += "\n";
    res += code;
    return res;
}
