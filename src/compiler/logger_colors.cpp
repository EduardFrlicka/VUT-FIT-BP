#include "logger.h"
#include <unistd.h>

std::string command(std::string command) {
    std::string result;
    FILE *out;
    char buffer[BUFSIZ];

    out = popen(command.c_str(), "r");
    if (!out)
        return "";

    while (!feof(out)) {
        fgets(buffer, BUFSIZ, out);
        result.append(buffer);
    }

    return result;
}

LoggerColors::LoggerColors() {
    int fileDesc;

    fileDesc = fileno(stderr);
    if (!isatty(fileDesc)) {
        return;
    }

    /* attributes */
    _reset = command("tput sgr0");
    _bold = command("tput bold");

    /* colors */
    _black = command("tput setaf 0");
    _red = command("tput setaf 1");
    _green = command("tput setaf 2");
    _yellow = command("tput setaf 3");
    _blue = command("tput setaf 4");
    _magenta = command("tput setaf 5");
    _cyan = command("tput setaf 6");
    _white = command("tput setaf 7");
}

void LoggerColors::reset() {
    fprintf(stderr, "%s", _reset.c_str());
}

void LoggerColors::bold() {
    fprintf(stderr, "%s", _bold.c_str());
}

void LoggerColors::black() {
    fprintf(stderr, "%s", _black.c_str());
}

void LoggerColors::red() {
    fprintf(stderr, "%s", _red.c_str());
}

void LoggerColors::green() {
    fprintf(stderr, "%s", _green.c_str());
}

void LoggerColors::yellow() {
    fprintf(stderr, "%s", _yellow.c_str());
}

void LoggerColors::blue() {
    fprintf(stderr, "%s", _blue.c_str());
}

void LoggerColors::magenta() {
    fprintf(stderr, "%s", _magenta.c_str());
}

void LoggerColors::cyan() {
    fprintf(stderr, "%s", _cyan.c_str());
}

void LoggerColors::white() {
    fprintf(stderr, "%s", _white.c_str());
}
