#pragma once

#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>

class Code {
  private:
    std::string code;
    std::set<std::string> include;

  public:
    Code();
    Code(const std::string &);
    Code(std::ifstream);
    Code(const std::string &, const std::set<std::string> &);
    // ~Code();

    Code apply(std::map<std::string, std::string>);

    std::string to_string();

    void replace(std::string, Code);
    void replace(std::regex, Code);
    void replace(std::regex, std::string);
    void replace(std::string, std::string);
    void uncomment(const std::string &);
    void append(Code);
    void append(std::vector<Code>);

    bool isEmpty();

  private:
};

class CodeFiles {
  private:
    Code free_code;
    std::map<std::string, Code> code_files;
    void replace(const std::string &, const CodeFiles &);
    bool contain_file(const std::string &);

  public:
    CodeFiles();
    CodeFiles(const std::map<std::string, Code> &);
    CodeFiles(const std::map<std::string, Code> &, const Code &);
    CodeFiles combine(const std::map<std::string, CodeFiles> &);
    CodeFiles combine(const std::string &, const CodeFiles &);
    void print();
};
