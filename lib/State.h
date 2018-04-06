#ifndef State_H
#define State_H

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
public:
    State() {};
    State(int number);
    int getID() const;
    void setType(Type t);
    Type getType() const;

    const State &operator=(const State &s);
    bool operator==(const State & s) const;
    static int newID()
    {
        return new_id++;
    }
};
bool operator<(const State &lhs, const State &rhs);

#endif // State_H
