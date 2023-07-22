#include "code.h"
#include "regex_constructor.h"
#include <regex>
#include <sstream>
#include <streambuf>

using namespace std;

Code::Code() {
}

Code::Code(const string &_code) {
    include = set<string>();
    string tmp(_code);

    regex include_regex("#include\\s+((<[^>]+>)|(\"[^\"]+\"))\n?");
    sregex_iterator i;

    for (i = sregex_iterator(tmp.begin(), tmp.end(), include_regex); i != sregex_iterator(); i++)
        include.insert((*i)[1].str());

    code = regex_replace(tmp, include_regex, "");
}

Code::Code(std::ifstream filestream) : Code(string(istreambuf_iterator<char>(filestream), istreambuf_iterator<char>())) {
}

Code::Code(const string &_code, const set<string> &_include = {}) : code(_code), include(_include) {
}

void Code::apply(regex key, string value) {
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

void Code::apply(std::string key, Code value) {
    include.merge(value.include);
    code = regex_replace(code, regex_replacement(key), value.code);
}

void Code::apply(regex key, Code value) {
    include.merge(value.include);
    code = regex_replace(code, key, value.code);
}

void Code::apply(std::string key, std::string value) {
    apply(regex_replacement(key), value);
}

void Code::uncomment(const std::string &key) {
    regex re = regex_optional("(.*?__" + key + "__.*?)");
    apply(re, "$1");
}

Code Code::apply(std::map<std::string, std::string> replacements) {
    Code out(code, include);

    for (auto kv : replacements) {
        out.uncomment(kv.first);
        out.apply(kv.first, kv.second);
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

bool Code::isEmpty() {
    return code.empty() && include.empty();
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
