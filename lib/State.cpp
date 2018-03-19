#include "State.h"
#include <string>

State::State()
	: id(-1)
{
	type = REGULAR;
}

State::State(int number, std::string mT)
	: id(number),matchToken(mT)
{
	type = REGULAR;
}

void State::setType(Type t)
{
	type = t;
}

Type State::getType() const { return type; }

int State::getID()const  { return id;}

std::string State::getMatchedToken() const{
	return matchToken;
}

bool operator<(const State &lhs, const State &rhs)
{
	return lhs.getID() < rhs.getID();
}
