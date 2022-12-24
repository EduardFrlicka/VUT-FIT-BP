#include <map>
#include <set>
#include <string>

using std::map;
using std::set;
using std::string;

class CodeTemplate {

  public:
    CodeTemplate(const string &);

    string apply(map<string, string> &);

  private:
    string text;
    set<string> required;
    set<string> optional;
};
