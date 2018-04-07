#ifndef State_H
#define State_H

#include <string>

enum Type
{
    REGULAR,
    STARTING,
    ACCEPTING,
};

class State
{
    static int new_id;
    int id;
    Type type;
    std::string tokenType;
public:
    State();
    State(int number);
    int getID() const;
    void setType(Type t);
    Type getType() const;

    void setTokenType(std::string str);
    std::string getTokenType() const;

    const State &operator=(const State &s);
    bool operator==(const State & s) const;
    static int newID()
    {
        return new_id++;
    }
};
bool operator<(const State &lhs, const State &rhs);

#endif // State_H
