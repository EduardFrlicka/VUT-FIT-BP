#pragma once

#include "file.h"
#include "logger.h"
#include "syntax_tree.h"

class SyntaxAnalyzer {
  public:
    SyntaxAnalyzer(Logger &);

    int analyze_file(File *file);

  private:
    File *file;
    Logger &logger;

    int expect_token(TokenType);
};
