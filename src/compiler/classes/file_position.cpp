#include "file_position.h"

FilePosition::FilePosition(FilePosition &_old) : filename(_old.filename), line(_old.line), col(_old.line) {
}

FilePosition::FilePosition(const char *_filename) : filename(_filename), line(1), col(0) {
}

FilePosition::FilePosition(const char *_filename, unsigned _line, unsigned _col) : filename(_filename), line(_line), col(_col) {
}

void FilePosition::inc_col() {
    col++;
}

void FilePosition::inc_line() {
    col = 0;
    line++;
}
