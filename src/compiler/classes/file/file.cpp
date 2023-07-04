#include "file.h"
#include "error.h"
#include "return_values.h"
#include <errno.h>
#include <string.h>

#define NO_CHAR -2

File::File(const char *_filename) : filename(_filename), pos(_filename) {
    this->ptr = nullptr;
    this->c = 0;
    this->c2 = NO_CHAR;
}

int File::init() {
    this->ptr = fopen(this->filename, "r");
    if (!this->ptr)
        ERROR(ERR_FILE, "file \"%s\" cannot be opened: %s", this->filename, strerror(errno));

    this->c = getc(this->ptr);

    return SUCCESS;
}

File::~File() {
    if (this->ptr)
        fclose(this->ptr);
}

Token *File::newToken() {
    Token *newToken = new Token(this->pos);
    this->tokenStack.append(newToken);
    return newToken;
}

int File::getchar() {
    int c = this->c;
    if (c != EOF) {
        if (c2 == NO_CHAR)
            this->c = getc(this->ptr);
        else {
            this->c = this->c2;
            c2 = NO_CHAR;
        }
    }

    if (c == '\n')
        pos.inc_line();

    pos.inc_col();

    return c;
}

int File::peekchar() {
    return this->c;
};

int File::peek2char() {
    if (this->c2 == NO_CHAR) {
        if (c == EOF)
            return EOF;
        this->c2 = getc(this->ptr);
    }

    return this->c2;
};

FilePosition &File::getPos() {
    return pos;
}
