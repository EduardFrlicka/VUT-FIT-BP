#ifndef FILE_H
#define FILE_H

#include "token.h"
#include <stdio.h>

class File {
  private:
    const char *filename;
    FILE *ptr;
    int c;

    unsigned line;
    unsigned col;

  public:
    TokenStack tokenStack;
    
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
    int peekchar();

    /**
     * @brief allocate new token, append to tokenstack
     * 
     * @return Token* new token
     */
    Token *newToken();


    File(const char *filename);
    
    /**
     * @brief initializaion of class, open file, initialize debug values
     * 
     * @return int 
     */
    int init();
    ~File();
};

#endif /* FILE_H */
