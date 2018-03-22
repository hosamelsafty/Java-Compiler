#ifndef LexicalAnalyzer_H
#define LexicalAnalyzer_H

#include "DFATransitionTable.h"
#include "Token.h"

#include <iostream>

class ErrorLog;

class LexicalAnalyzer
{
public:
//    LexicalAnalyzer(DFATransitionTable &transitionTable, std::istream& in, ErrorLog &errorLog);
    LexicalAnalyzer(DFATransitionTable &transitionTable, std::istream& in);
    ~LexicalAnalyzer();
    Token* nextToken();
private:
    Token* getToken(std::istream&);
    std::istream& input;
//    ErrorLog& errLog;
    DFATransitionTable& dfa_t;
    std::string remainingInput;
};

#endif // LexicalAnalyzer_H
