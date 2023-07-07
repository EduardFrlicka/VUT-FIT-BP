#include "file_position.h"
#include "error.h"

FilePosition::FilePosition(const std::string &_filename) : filename(_filename), line(1), col(1) {
}

FilePosition::FilePosition(const std::string &_filename, unsigned _line, unsigned _col) : filename(_filename), line(_line), col(_col) {
}

void FilePosition::inc_col() {
    col++;
}

void FilePosition::inc_line() {
    col = 0;
    line++;
}
