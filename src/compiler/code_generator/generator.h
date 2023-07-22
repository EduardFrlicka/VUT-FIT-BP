#include "arguments.h"
#include "code.h"
#include "syntax_tree.h"
#include "template.h"
#include <filesystem>
#include <map>

class CodeGenerator {
  public:
    CodeGenerator(const ast::Classes &);

  private:
    // CodeFiles static_files;
    CodeFiles result;
    CodeTemplateManager template_manager;
    std::map<std::string, std::string> names;

    CodeFiles generate_classes(const ast::Classes &);
    CodeFiles generate_class(const ast::Class &);
    CodeFiles generate_object_net(const ast::ObjectNet &);
    CodeFiles load_static_code_files(std::filesystem::path);
};
