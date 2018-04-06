#ifndef LexicalAnalyzer_H
#define LexicalAnalyzer_H

#include "DFATransitionTable.h"
#include "Token.h"
#include "StreamWrapper.h"

#include <iostream>

class ErrorLog;
class SymbolTable;

class LexicalAnalyzer
{
public:
    LexicalAnalyzer(DFATransitionTable &transitionTable, std::istream& in, ErrorLog *errorLog = nullptr, SymbolTable *symbolTable = nullptr);
    ~LexicalAnalyzer();

    Token* nextToken();

private:
    DFATransitionTable& dfa_t;
    StreamWrapper _streamWrapper;
    ErrorLog * errorLog;
    SymbolTable * symbolTable;
};

#endif // LexicalAnalyzer_H
