#ifndef ErrorLog_H
#define ErrorLog_H

#include <string>

class ErrorLog
{
public:
    ErrorLog();
    ~ErrorLog();

    void add(const std::string &lexeme, int lineNumber, int positionInLine, const std::string &message);

private:

};

std::ostream& operator<<(std::ostream& out, const ErrorLog &errorLog);

#endif // ErrorLog_H