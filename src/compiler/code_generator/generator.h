#include "arguments.h"
#include "code.h"
#include "semantic_graph.h"
#include "template.h"
#include <filesystem>
#include <map>

class CodeGenerator {
  public:
    CodeGenerator(const asg::Classes &);

  private:
    // CodeFiles static_files;
    CodeFiles result;
    CodeTemplateManager template_manager;
    std::map<std::string, std::string> names;

    CodeFiles generate(const asg::Classes &);
    CodeFiles generate(const asg::Class &);
    CodeFiles generate(const asg::Net &);
    CodeFiles generate(const asg::Method &);
    CodeFiles generate(const asg::Constructor &);
    CodeFiles generate(const asg::SynPort &);
    
    CodeFiles generate(const asg::Place &);
    CodeFiles generate(const asg::Transition &);

    CodeFiles load_static_code_files(std::filesystem::path);
};
