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

    void apply(std::string, Code);
    void apply(std::regex, Code);
    void apply(std::regex, std::string);
    void apply(std::string, std::string);
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
    bool contain_file(const std::string &);

  public:
    CodeFiles();
    CodeFiles(const std::map<std::string, Code> &);
    CodeFiles(const std::map<std::string, Code> &, const Code &);

    // void remove_slot(const std::string&);

    void apply(const std::map<std::string, CodeFiles> &);
    void apply(const std::string &, const CodeFiles &);
    void apply(const std::string &slot_key, const std::string &slot_value);
    void apply(const std::map<std::string, std::string> &);
    void print();
};
