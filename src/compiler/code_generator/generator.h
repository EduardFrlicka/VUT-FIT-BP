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

    CodeFiles load_static_code_files(std::filesystem::path);

    CodeFiles generate(const asg::Classes &node);
    CodeFiles generate(const asg::Class &node);
    CodeFiles generate(const asg::Net &node);
    CodeFiles generate(const asg::Method &node);
    CodeFiles generate(const asg::Constructor &node);
    CodeFiles generate(const asg::SynPort &node);

    CodeFiles generate(const asg::Place &node);
    CodeFiles generate(const asg::Transition &node);

    CodeFiles generate(const asg::PreCondPair &node);
    CodeFiles generate(const asg::PostCondPair &node);
    CodeFiles generate(const asg::CondPair &node);
    CodeFiles generate(const asg::Guard &node);
    CodeFiles generate(const asg::Action &node);

    CodeFiles generate(const asg::MultiSet &node);
    CodeFiles generate(const asg::MultiSetElemPair &node);
    CodeFiles generate(const asg::MultiSetCount &node);
    CodeFiles generate(const asg::MultiSetTerm &node);
    CodeFiles generate(const asg::MultiSetList &node);

    CodeFiles generate_argument(const Identifier &id);
    CodeFiles generate_temporary(const Identifier &id);

    CodeFiles generate(const asg::Expression &node);
    CodeFiles generate(const asg::Expressions &node);
    CodeFiles generate(const asg::Assigment &node);
    CodeFiles generate(const asg::KeywordMessage &node);
    CodeFiles generate(const asg::BinaryMessage &node);
    CodeFiles generate(const asg::UnaryMessage &node);
    CodeFiles generate(const asg::Literal &node);
    CodeFiles generate(const asg::Variable &node);
    CodeFiles generate(const asg::ClassRef &node);
    CodeFiles generate(const asg::Bracket &node);
    CodeFiles generate(const asg::CodeBlock &node);
    CodeFiles generate(const asg::ConstArray &node);
};
