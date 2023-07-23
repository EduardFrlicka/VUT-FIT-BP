#include "logger.h"
#include <errno.h>
#include <stdarg.h>

Logger logger;

Logger::Logger() : colors() {
}

Logger::~Logger() {
}

void Logger::print_position(const TokenStackIterator &iterator) {
    print_position(iterator.it->pos);
}

void Logger::print_position(const Token &token) {
    print_position(token.pos);
}

void Logger::print_position(const FilePosition &pos) {
    colors.reset();
    colors.bold();
    fprintf(stderr, "%s:%u:%u: ", pos.filename.c_str(), pos.line, pos.col);
    colors.reset();
}

void Logger::print_position(const std::filesystem::path &filepath) {
    colors.reset();
    colors.bold();
    fprintf(stderr, "%s: ", filepath.c_str());
    colors.reset();
}

void Logger::print_line(const Token &token, void (LoggerColors::*colorFunc)(void)) {
    print_line(token.it, colorFunc);
}

void Logger::print_line(const TokenStackIterator &iterator, void (LoggerColors::*colorFunc)(void)) {
    std::deque<Token>::iterator start = iterator.it;
    std::deque<Token>::iterator it;
    size_t size;
    std::string underline;

    /* find first token in line */
    while (start->type != tokenEOL && start > iterator._begin)
        start--;
    start++;

    /* print left margin */
    fprintf(stderr, "%5u |", iterator.it->pos.line);

    /* print all tokens from line before "token" */
    for (it = start; it < iterator.it; it++)
        fprintf(stderr, "%s", it->text.c_str());

    /* colored print of "token" */
    colors.bold();
    (colors.*colorFunc)();
    size = fprintf(stderr, "%s", iterator.it->text.c_str());
    colors.reset();

    /* pritn all tokens in line after "token" */

    if (iterator.it->type != tokenEOL) {
        for (it = iterator.it + 1; it < iterator._end && it->type != tokenEOL; it++)
            fprintf(stderr, "%s", it->text.c_str());
        fprintf(stderr, "\n");
    }

    /* construct underline */
    underline = "^";
    size = size ? size : 1;
    underline.append(std::string(size - 1, '~'));

    /* print left margin */
    fprintf(stderr, "      |");

    /* print whitespace until "token" position */
    for (it = start; it < iterator.it; it++)
        if (it->type != tokenWhiteSpace)
            fprintf(stderr, "%*.s", (int)it->text.length(), "");
        else
            fprintf(stderr, "%s", it->text.c_str());

    /* print colored underline */
    colors.bold();
    (colors.*colorFunc)();
    fprintf(stderr, "%s", underline.c_str());
    colors.reset();

    fprintf(stderr, "\n");
    fflush(stderr);
}

void Logger::c_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    c_error(fmt, args);
    va_end(args);
}

void Logger::c_error(const FilePosition &pos, const char *fmt, ...) {
    print_position(pos);

    va_list args;
    va_start(args, fmt);
    c_error(fmt, args);
    va_end(args);
}

void Logger::c_error(const Token &token, const char *fmt, ...) {
    print_position(token);

    va_list args;
    va_start(args, fmt);
    c_error(fmt, args);
    va_end(args);

    print_line(token, &LoggerColors::red);
}

void Logger::c_error(const TokenStackIterator &iterator, const char *fmt, ...) {
    print_position(iterator);

    va_list args;
    va_start(args, fmt);
    c_error(fmt, args);
    va_end(args);

    print_line(iterator, &LoggerColors::red);
}

void Logger::c_error(const std::filesystem::path &filepath, const char *fmt, ...) {
    print_position(filepath);

    va_list args;
    va_start(args, fmt);
    c_error(fmt, args);
    va_end(args);
}

void Logger::c_error(const char *fmt, va_list args) {
    colors.reset();
    colors.bold();
    colors.red();

    fprintf(stderr, "error: ");

    colors.reset();

    vfprintf(stderr, fmt, args);

    fprintf(stderr, "\n");
    colors.reset();
    fflush(stderr);
}

void Logger::c_warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    c_warning(fmt, args);
    va_end(args);
}

void Logger::c_warning(const FilePosition &pos, const char *fmt, ...) {
    print_position(pos);

    va_list args;
    va_start(args, fmt);
    c_warning(fmt, args);
    va_end(args);
}

void Logger::c_warning(const Token &token, const char *fmt, ...) {
    print_position(token);

    va_list args;
    va_start(args, fmt);
    c_warning(fmt, args);
    va_end(args);

    print_line(token, &LoggerColors::magenta);
}

void Logger::c_warning(const TokenStackIterator &iterator, const char *fmt, ...) {
    print_position(iterator);

    va_list args;
    va_start(args, fmt);
    c_warning(fmt, args);
    va_end(args);

    print_line(iterator, &LoggerColors::magenta);
}

void Logger::c_warning(const std::filesystem::path &filepath, const char *fmt, ...) {
    print_position(filepath);

    va_list args;
    va_start(args, fmt);
    c_warning(fmt, args);
    va_end(args);
}

void Logger::c_warning(const char *fmt, va_list args) {
    colors.reset();
    colors.bold();
    colors.magenta();

    fprintf(stderr, "warning: ");

    colors.reset();

    vfprintf(stderr, fmt, args);

    fprintf(stderr, "\n");
    colors.reset();
    fflush(stderr);
}

void Logger::c_note(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    c_note(fmt, args);
    va_end(args);
}

void Logger::c_note(const FilePosition &pos, const char *fmt, ...) {
    print_position(pos);

    va_list args;
    va_start(args, fmt);
    c_note(fmt, args);
    va_end(args);
}

void Logger::c_note(const Token &token, const char *fmt, ...) {
    print_position(token);

    va_list args;
    va_start(args, fmt);
    c_note(fmt, args);
    va_end(args);

    print_line(token, &LoggerColors::cyan);
}

void Logger::c_note(const TokenStackIterator &iterator, const char *fmt, ...) {
    print_position(iterator);

    va_list args;
    va_start(args, fmt);
    c_note(fmt, args);
    va_end(args);

    print_line(iterator, &LoggerColors::cyan);
}

void Logger::c_note(const std::filesystem::path &filepath, const char *fmt, ...) {
    print_position(filepath);

    va_list args;
    va_start(args, fmt);
    c_note(fmt, args);
    va_end(args);
}

void Logger::c_note(const char *fmt, va_list args) {
    colors.reset();
    colors.bold();
    colors.cyan();

    fprintf(stderr, "note: ");

    colors.reset();

    vfprintf(stderr, fmt, args);

    fprintf(stderr, "\n");
    colors.reset();
    fflush(stderr);
}
