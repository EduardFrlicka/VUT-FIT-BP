#include "file.h"
#include "error.h"
#include "return_values.h"
#include <errno.h>
#include <string.h>

#define NO_CHAR -2

FileReader::FileReader(const std::string &_filename) : super(_filename), pos(_filename) {
}

int FileReader::get() {
    int c = super::get();

    if (c == '\n')
        pos.inc_line();

    pos.inc_col();

    return c;
}

int FileReader::peek() {
    return super::peek();
};

int FileReader::peek2() {
    int c;

    super::get();
    c = super::peek();
    super::unget();

    return c;
}

FilePosition &FileReader::getPos() {
    return pos;
}
