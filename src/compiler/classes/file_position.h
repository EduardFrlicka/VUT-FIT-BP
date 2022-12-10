#pragma once

class FilePosition {
  public:
    FilePosition(FilePosition &);
    FilePosition(const char *);
    FilePosition(const char *, unsigned, unsigned);

    const char *filename;
    unsigned line;
    unsigned col;

    void inc_line();
    void inc_col();
};
