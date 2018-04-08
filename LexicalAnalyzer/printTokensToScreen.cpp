#include "printTokensToScreen.h"
#include <iostream>

void printTokensToScreen(LexicalAnalyzer &lexicalAnalyzer)
{
    Token * token = nullptr;
    while (token = lexicalAnalyzer.nextToken())
    {
        std::cout << token->type << " " << token->value << std::endl;
    }
}
