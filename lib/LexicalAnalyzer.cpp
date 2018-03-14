#include "LexicalAnalyzer.h"
#include "ErrorLog.h"

LexicalAnalyzer::LexicalAnalyzer(const TransitionTable &transitionTable, std::istream& in, ErrorLog &errorLog)
{

}

LexicalAnalyzer::~LexicalAnalyzer()
{

}

Token LexicalAnalyzer::nextToken()
{
	return Token();
}
