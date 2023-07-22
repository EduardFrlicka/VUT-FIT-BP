#pragma once
#include "code.h"
#include <filesystem>
#include <map>
#include <set>
#include <string>

class CodeTemplate;

class CodeTemplateManager {
  private:
    std::map<std::string, CodeFiles> templates;

  public:
    CodeTemplateManager(const std::filesystem::path &);

    CodeFiles get(const std::string);

  private:
    void initialize(const std::filesystem::path &);
    CodeFiles create_template(std::istream &);
    CodeFiles create_template(const std::filesystem::path &);

    std::filesystem::path template_name(const std::filesystem::path &, const std::filesystem::path &);
};
