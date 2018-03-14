#ifndef LexicalAnalyzer_H
#define LexicalAnalyzer_H

#include "TransitionTable.h"
#include "Token.h"

#include <iostream>

class ErrorLog;

class LexicalAnalyzer
{
public:
    LexicalAnalyzer(const TransitionTable &transitionTable, std::istream& in, ErrorLog &errorLog);
    ~LexicalAnalyzer();

    Token nextToken();
};

#endif // LexicalAnalyzer_H
