#pragma once

#include "file.h"
#include "logger.h"
#include "token.h"

class LexicalAnalyzer {
  public:
    LexicalAnalyzer(Logger &);

    int analyze_file(File *file);

  private:
    int analyze_token();
    int start(int);
    int end(int);

    Token *token;

    int (LexicalAnalyzer::*currState)(int);
    int (LexicalAnalyzer::*nextState)(int);

    File *file;
    Logger &logger;
};

typedef int (LexicalAnalyzer::*state)(void);