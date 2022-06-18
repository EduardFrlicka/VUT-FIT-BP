#ifndef FILE_H
#define FILE_H

#include "token.h"
#include <stdio.h>

class cFile {
  private:
    char *filename;
    FILE *ptr;
    int c;

    unsigned line;
    unsigned col;

  public:
    cTokenStack tokenStack;

    int getchar();

    int peakchar();

    cToken *newToken();

    cFile(char *filename);
    int init();
    ~cFile();
};

#endif /* FILE_H */
