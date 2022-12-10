#include "logger.h"
#include <errno.h>
#include <stdarg.h>

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
    fprintf(stderr, "%s:%u:%u: ", pos.filename, pos.line, pos.col);
}

void Logger::error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    error(fmt, args);
    va_end(args);
}

void Logger::error_at(Token &token, const char *fmt, ...) {
    print_position(token);

    va_list args;
    va_start(args, fmt);
    error(fmt, args);
    va_end(args);
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

void Logger::warning_at(Token &token, const char *fmt, ...) {
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

void Logger::note_at(Token &token, const char *fmt, ...) {
    print_position(token);

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
