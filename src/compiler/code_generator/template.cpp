#include "template.h"
#include "error.h"
#include "return_values.h"
#include <iostream>
#include <regex>

CodeTemplate::CodeTemplate(const string &_text) : text(_text) {
    using namespace std;
    /* regex for optional replacement */
    regex regexOptional("/\\*\\s*__(\\w+(_\\w+)*)__\\s*\\*/"); //  /* __name__ */
    /* regex for non */
    regex regexRequired("__(\\w+(_\\w+)*)__"); //  __name__

    smatch res;

    /** @see: https://cplusplus.com/reference/regex/regex_token_iterator/regex_token_iterator/*/
    regex_token_iterator<string::iterator> rend;
    regex_token_iterator<string::iterator> iteratorRequired(text.begin(), text.end(), regexRequired, 1);
    regex_token_iterator<string::iterator> iteratorOptional(text.begin(), text.end(), regexOptional, 1);

    while (iteratorOptional != rend) {
        string match = *iteratorOptional++;

        if (optional.find(match) != optional.end())
            continue;

        optional.insert(match);
    }

    while (iteratorRequired != rend) {
        string match = *iteratorRequired++;

        if (optional.find(match) != optional.end())
            continue;
        if (required.find(match) != required.end())
            continue;

        required.insert(match);
    }

    cout << "optional" << endl;
    for (auto i : optional) {
        cout << i << endl;
    }

    cout << "replacement" << endl;
    for (auto i : required) {
        cout << i << endl;
    }
}

string CodeTemplate::apply(map<string, string> &replacements) {
    using namespace std;

    string result = text;

    for (auto i : required) {
        if (replacements.find(i) == replacements.end())
            ERROR("", "Needed field (%s) not found when trying to apply code template", i.c_str());
        regex replaceRegex("__" + i + "__");

        result = regex_replace(result, replaceRegex, replacements[i]);
    }

    for (auto i : optional) {
        regex replaceRegex("/\\*\\s*__" + i + "__\\s*\\*/");
        string replacement = "";
        if (replacements.find(i) != replacements.end())
            replacement = replacements[i];
        result = regex_replace(result, replaceRegex, replacement);
    }

    return result;
};
