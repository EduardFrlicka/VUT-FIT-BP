#pragma once

#include "file_position.h"
#include "token.h"
#include <filesystem>
#include <stdio.h>
#include <string>

class LoggerColors {
  public:
    LoggerColors();

    /* attributes */
    void reset();
    void bold();

    /* colors */
    void black();
    void red();
    void green();
    void yellow();
    void blue();
    void magenta();
    void cyan();
    void white();

  private:
    /* attributes */
    std::string _reset;
    std::string _bold;

    /* colors */
    std::string _black;
    std::string _red;
    std::string _green;
    std::string _yellow;
    std::string _blue;
    std::string _magenta;
    std::string _cyan;
    std::string _white;
};

class Logger {
  public:
    Logger();
    ~Logger();

    void error(const char *, ...);
    void error(const FilePosition &, const char *, ...);
    void error(const Token &, const char *, ...);
    void error(const char *, va_list);

    void warning(const char *, ...);
    void warning(const FilePosition &, const char *, ...);
    void warning(const Token &, const char *, ...);
    void warning(const char *, va_list);

    void note(const char *, ...);
    void note(const FilePosition &, const char *, ...);
    void note(const Token &, const char *, ...);
    void note(const std::filesystem::path &, const char *, ...);
    void note(const char *, va_list);

  private:
    void print_position(const Token &);
    void print_position(const FilePosition &);
    void print_position(const std::filesystem::path &);

    void print_line(const Token &token, void (LoggerColors::*colorFunc)(void));
    FILE *filePtr;
    LoggerColors colors;
};

extern Logger logger;