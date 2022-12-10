#pragma once

#include "file.h"
#include "logger.h"
#include "token.h"

class LexicalAnalyzer {
  public:
    LexicalAnalyzer(Logger &);

    int analyze_file(File *file);

  private:
    Token *token;

    int (LexicalAnalyzer::*currState)(int);
    int (LexicalAnalyzer::*nextState)(int);

    File *file;
    Logger &logger;

    int analyze_token();
    int start(int);
    int number(int);
    int dollar(int);
    int character(int);
    int identifier(int);
    int minus(int);
    int stropen(int);
    int str(int);
    int whitespace(int);
    int end(int);
};

typedef int (LexicalAnalyzer::*state)(void);
