#include "ErrorLog.h"

ErrorLog::ErrorLog()
{

}

ErrorLog::~ErrorLog()
{

}

void ErrorLog::add(const std::string &lexeme, int lineNumber, int positionInLine, const std::string &message)
{

}


std::ostream& operator<<(std::ostream& out, const ErrorLog &errorLog)
{
    return out;
}
