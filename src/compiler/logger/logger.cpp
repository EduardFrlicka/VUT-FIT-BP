#include "logger.h"
#include <errno.h>
#include <stdarg.h>

Logger logger;

Logger::Logger() : colors() {
}

Logger::~Logger() {
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
    const Token *ptr;
    const Token *start;
    size_t size;
    std::string underline;

    /* find first token in line */
    for (ptr = &token; ptr->prev && ptr->prev->type != tokenEOL; ptr = ptr->prev) {
    }
    start = ptr;

    /* print left margin */
    fprintf(stderr, "%5u |", token.pos.line);

    /* print all tokens from line before "token" */
    for (ptr = start; ptr && ptr != &token; ptr = ptr->next)
        fprintf(stderr, "%s", ptr->text.c_str());

    /* colored print of "token" */
    colors.bold();
    (colors.*colorFunc)();
    size = fprintf(stderr, "%s", token.text.c_str());
    colors.reset();

    /* pritn all tokens in line after "token" */
    if (token.type != tokenEOL) {
        for (ptr = token.next; ptr && ptr->type != tokenEOL; ptr = ptr->next) {
            fprintf(stderr, "%s", ptr->text.c_str());
        }
        fprintf(stderr, "\n");
    }

    /* construct underline */
    underline = "^";
    size = size ? size : 1;
    underline.append(std::string(size - 1, '~'));

    /* print left margin */
    fprintf(stderr, "      |");

    /* print whitespace until "token" position */
    for (ptr = start; ptr && ptr != &token; ptr = ptr->next)
        if (ptr->type != tokenWhiteSpace)
            fprintf(stderr, "%*.s", (int)ptr->text.length(), "");
        else
            fprintf(stderr, "%s", ptr->text.c_str());

    /* print colored underline */
    colors.bold();
    (colors.*colorFunc)();
    fprintf(stderr, "%s", underline.c_str());
    colors.reset();

    fprintf(stderr, "\n");
}

void Logger::error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    error(fmt, args);
    va_end(args);
}

void Logger::error(const FilePosition &pos, const char *fmt, ...) {
    print_position(pos);

    va_list args;
    va_start(args, fmt);
    error(fmt, args);
    va_end(args);
}

void Logger::error(const Token &token, const char *fmt, ...) {
    print_position(token);

    va_list args;
    va_start(args, fmt);
    error(fmt, args);
    va_end(args);

    print_line(token, &LoggerColors::red);
}

void Logger::error(const char *fmt, va_list args) {
    colors.reset();
    colors.bold();
    colors.red();

    fprintf(stderr, "error: ");

    colors.reset();

    vfprintf(stderr, fmt, args);

    fprintf(stderr, "\n");
    colors.reset();
}

void Logger::warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    warning(fmt, args);
    va_end(args);
}

void Logger::warning(const FilePosition &pos, const char *fmt, ...) {
    print_position(pos);

    va_list args;
    va_start(args, fmt);
    warning(fmt, args);
    va_end(args);
}

void Logger::warning(const Token &token, const char *fmt, ...) {
    print_position(token);

    va_list args;
    va_start(args, fmt);
    warning(fmt, args);
    va_end(args);
}

void Logger::warning(const char *fmt, va_list args) {
    colors.reset();
    colors.bold();
    colors.magenta();

    fprintf(stderr, "warning: ");

    colors.reset();

    vfprintf(stderr, fmt, args);

    fprintf(stderr, "\n");
    colors.reset();
}

void Logger::note(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    note(fmt, args);
    va_end(args);
}

void Logger::note(const FilePosition &pos, const char *fmt, ...) {
    print_position(pos);

    va_list args;
    va_start(args, fmt);
    note(fmt, args);
    va_end(args);
}

void Logger::note(const Token &token, const char *fmt, ...) {
    print_position(token);

    va_list args;
    va_start(args, fmt);
    note(fmt, args);
    va_end(args);
}

void Logger::note(const std::filesystem::path &filepath, const char *fmt, ...) {
    print_position(filepath);

    va_list args;
    va_start(args, fmt);
    note(fmt, args);
    va_end(args);
}

void Logger::note(const char *fmt, va_list args) {
    colors.reset();
    colors.bold();
    colors.cyan();

    fprintf(stderr, "note: ");

    colors.reset();

    vfprintf(stderr, fmt, args);

    fprintf(stderr, "\n");
    colors.reset();
}
