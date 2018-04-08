#ifndef State_H
#define State_H

#include <string>

enum Type
{
    REGULAR,
    STARTING,
    ACCEPTING,
};

typedef int StateId;

class State
{
    static StateId new_id;
    StateId id;

    std::string tokenType;
    int priority;

    Type type;
public:
    State();
    State(StateId number);
    StateId getID() const;
    void setType(Type t);
    Type getType() const;

    void setTokenType(std::string str);
    std::string getTokenType() const;

    void setPriority(int p);
    int getPriority() const;

    //const State &operator=(const State &s);

    bool operator==(const State & s) const;
    static StateId newID()
    {
        return new_id++;
    }
};

bool operator<(const State &lhs, const State &rhs);

#endif // State_H
