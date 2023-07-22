#pragma once
#include "code.h"
#include <filesystem>
#include <map>
#include <set>
#include <string>

class CodeTemplate;

class CodeTemplateManager {
  private:
    std::map<std::string, CodeTemplate> templates;

  public:
    CodeTemplateManager(const std::filesystem::path &);

    CodeTemplate get(const std::string);

  private:
    void initialize(const std::filesystem::path &);
    std::filesystem::path template_name(const std::filesystem::path &, const std::filesystem::path &);
};

class CodeTemplate {

  public:
    CodeTemplate();
    CodeTemplate(const std::string &);
    CodeTemplate(const std::filesystem::directory_entry &);
    CodeTemplate(const std::filesystem::path &);

    void print();
    CodeFiles apply(const std::map<std::string, std::string> &);

  private:
    std::string replace(const std::string &, const std::map<std::string, std::string> &);
    void initialize(std::istream &);
    std::map<std::string, Code> code_files;

    // std::string text;
    // std::set<std::string> required;
    // std::set<std::string> optional;
};
