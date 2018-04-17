#ifndef LexicalAnalyzer_H
#define LexicalAnalyzer_H

#include "DFATransitionTable.h"
#include "AcceptedTokenMap.h"
#include "Token.h"

#include <iostream>

class ErrorLog;

class LexicalAnalyzer
{
public:
    LexicalAnalyzer(DFATransitionTable &transitionTable, std::istream& in, ErrorLog &errorLog);
    ~LexicalAnalyzer();
    Token* nextToken();
private:
    void getToken(std::istream& ,
    		std::string&, int &indx, int &lastAccIndx,
    		State& ,State& );
    std::istream& input;
    int noLine;
    ErrorLog& errLog;
    DFATransitionTable& dfa_t;
    std::string remainingInput;
};

#endif // LexicalAnalyzer_H
