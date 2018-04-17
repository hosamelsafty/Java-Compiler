#ifndef ErrorLog_H
#define ErrorLog_H

#include <string>
#include <map>

class ErrorLog
{
public:
    ErrorLog();
    ~ErrorLog();

    void add(const std::string &lexeme, int lineNumber, const std::string &message);

    std::map<int,std::pair<std::string,std::string > > elog;
};

std::ostream& operator<<(std::ostream& out, const ErrorLog &errorLog);
#endif // ErrorLog_H
