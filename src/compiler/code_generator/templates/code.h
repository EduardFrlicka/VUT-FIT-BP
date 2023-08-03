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

    Code apply(const std::map<std::string, std::string> &);

    std::string to_string() const;

    void apply(std::string, Code);
    void apply(std::regex, Code);
    void apply(std::regex, std::string);
    void apply(std::string, std::string);
    void uncomment(const std::string &);
    void append(Code);
    void append(std::vector<Code>);

    bool isEmpty() const;
    bool contains_slot(const std::string &slot_name) const;

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
    const std::map<std::string, Code> &get_code_files() const;

    void apply(const std::map<std::string, CodeFiles> &);
    void apply(const std::string &, const CodeFiles &);
    void apply(const std::string &slot_key, const std::string &slot_value);
    void apply(const std::map<std::string, std::string> &);
    void remove_optional_slots();
    void remove_optional_slots_from_filenames();
    void print();
};
