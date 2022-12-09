#pragma once

#include "token.h"
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

    void print_location(Token &);

    void error(const char *, ...);
    void error_at(Token &, const char *, ...);
    void error(const char *, va_list);

    void warning(const char *, ...);
    void warning_at(Token &, const char *, ...);
    void warning(const char *, va_list);

    void note(const char *, ...);
    void note_at(Token &, const char *, ...);
    void note(const char *, va_list);

  private:
    FILE *filePtr;
    LoggerColors colors;
};
