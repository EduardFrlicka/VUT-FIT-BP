#pragma once
#include <string>
class FilePosition {
  public:
    FilePosition(const std::string &);
    FilePosition(const std::string &, unsigned, unsigned);

    std::string filename;
    unsigned line;
    unsigned col;

    void inc_line();
    void inc_col();
};
