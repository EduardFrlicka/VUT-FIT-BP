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
    int stateWhitespace(int);

    /* literals */

    int stateNumber(int);
    int stateCharacter(int);
    int stateIdentifier(int);
    int stateStringOpen(int);
    int stateString(int);
    int stateSymbol(int);

    /* brackets */

    /* ( */
    int stateLeftRoundBracket(int);
    /* ) */
    int stateRightRoundBracket(int);
    /* { */
    int stateLeftCurlyBracket(int);
    /* } */
    int stateRightCurlyBracket(int);
    /* [ */
    int stateLeftSquareBracket(int);
    /* ] */
    int stateRightSquareBracket(int);

    /* operators */

    /* + */
    int stateAdd(int);
    /* - */
    int stateSub(int);
    /* / */
    int stateIDiv(int);
    /* * */
    int stateMul(int);
    /* = */
    int stateEq(int);
    /* ~= */
    int stateNotEq(int);
    /* == */
    int stateEqIdentity(int);
    /* ~== */
    int stateNotEqIdentity(int);
    /* < */
    int stateLess(int);
    /* > */
    int stateGreater(int);
    /* <= */
    int stateLessEq(int);
    /* >= */
    int stateGreaterEq(int);
    /* & */
    int stateAnd(int);
    /* | */
    int stateOr(int);
    /* \\ */
    int stateMod(int);
    /* // */
    int stateDiv(int);

    /* symbols */

    /* . */
    int stateDot(int);
    /* , */
    int stateComma(int);
    /* : */
    int stateColon(int);
    /* := */
    int stateAssign(int);

    /* intermediate states */

    /* \ */
    int stateBackslash(int);
    /* ~ */
    int stateTilde(int);
    /* $ */
    int stateDollar(int);
    /* # */
    int stateHash(int);

    int end(int);
};

typedef int (LexicalAnalyzer::*state)(void);
