#include "State.h"
#include <iostream>

StateId State::new_id = 0;

State::State()
    : id(State::newID()), type(REGULAR), priority(0)
{
}

State::State(StateId number)
    : id(number), type(REGULAR), priority(0)
{
}

void State::setType(Type t)
{
    type = t;
}

Type State::getType() const { return type; }

int State::getID()const { return id; }

void State::setTokenType(std::string str)
{
    tokenType = str;
}

std::string State::getTokenType() const
{
    return tokenType;
}

void State::setPriority(int p)
{
    priority = p;
}

int State::getPriority() const
{
    return priority;
}

bool State::operator==(const State & s) const
{
    return id == s.getID();
}

bool operator<(const State &lhs, const State &rhs)
{
    return lhs.getID() < rhs.getID();
}

//const State &State::operator=(const State &s)
//{
//    id = s.getID();
//    type = s.getType();
//
//    return *this;
//}
