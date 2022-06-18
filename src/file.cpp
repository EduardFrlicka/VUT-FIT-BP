#include "file.h"

cFile::cFile(char *filename) {
    this->filename = filename;
    this->ptr = nullptr;

    this->c = 0;
    this->col = 0;
    this->line = 0;
}

int cFile::init() {
    this->ptr = fopen(filename, "r");
    if (!this->ptr)
        return ERR_FILE;

    this->c = getc(this->ptr);
    this->col = 1;
    this->line = 1;

    return SUCCESS;
}

cFile::~cFile() {
    if (this->ptr)
        fclose(this->ptr);
}

cToken *cFile::newToken() {
    cToken *newToken = new cToken(this->filename, this->line, this->col);
    this->tokenStack.append(newToken);
    return newToken;
}

int cFile::getchar() {
    int c = this->c;
    if (c != EOF)
        this->c = getc(this->ptr);
    
    if(c=='\n'){
        this->line++;
        this->col=0;
    }

    this->col++;

    return c;
}

int cFile::peakchar() {
    return this->c;
};