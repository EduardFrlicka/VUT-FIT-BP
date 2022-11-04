#ifndef FILE_H
#define FILE_H

#include "token.h"
#include <stdio.h>

class cFile {
  private:
    const char *filename;
    FILE *ptr;
    int c;

    unsigned line;
    unsigned col;

  public:
    cTokenStack tokenStack;
    
    /**
     * @brief return current character, read next one
     * 
     * @return int 
     */
    int getchar();

    /**
     * @brief return character without reading next one 
     * 
     * @return int 
     */
    int peakchar();

    /**
     * @brief allocate new token, append to tokenstack
     * 
     * @return cToken* new token
     */
    cToken *newToken();


    cFile(const char *filename);
    
    /**
     * @brief initializaion of class, open file, initialize debug values
     * 
     * @return int 
     */
    int init();
    ~cFile();
};

#endif /* FILE_H */
