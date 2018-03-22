#ifndef Token_H
#define Token_H
#include <string>
using namespace std;

class Token
{
public:
    string type,value;
    Token(string t,string v);
    virtual ~Token();
};

#endif // Token_H