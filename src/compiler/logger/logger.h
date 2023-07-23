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


    void c_error(const char *, ...);
    void c_error(const FilePosition &, const char *, ...);
    void c_error(const Token &, const char *, ...);
    void c_error(const TokenStackIterator &, const char *, ...);
    void c_error(const std::filesystem::path &, const char *, ...);
    void c_error(const char *, va_list);

    void c_warning(const char *, ...);
    void c_warning(const FilePosition &, const char *, ...);
    void c_warning(const Token &, const char *, ...);
    void c_warning(const TokenStackIterator &, const char *, ...);
    void c_warning(const std::filesystem::path &, const char *, ...);
    void c_warning(const char *, va_list);

    void c_note(const char *, ...);
    void c_note(const FilePosition &, const char *, ...);
    void c_note(const Token &, const char *, ...);
    void c_note(const TokenStackIterator &, const char *, ...);
    void c_note(const std::filesystem::path &, const char *, ...);
    void c_note(const char *, va_list);

  private:
    void print_position(const TokenStackIterator &);
    void print_position(const Token &);
    void print_position(const FilePosition &);
    void print_position(const std::filesystem::path &);

    void print_line(const Token &token, void (LoggerColors::*colorFunc)(void));
    void print_line(const TokenStackIterator &iterator, void (LoggerColors::*colorFunc)(void));
    FILE *filePtr;
    LoggerColors colors;
};

extern Logger logger;