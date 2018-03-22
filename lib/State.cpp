#include "State.h"

int State::new_id = 0;
State::State(int number)
	: id(number)
{
	type = REGULAR;
}

void State::setType(Type t)
{
	type = t;
}

Type State::getType() const { return type; }

int State::getID()const  { return id;}

bool operator == (const State &lhs, const State &rhs)
{
	return lhs.getID() == rhs.getID();
}
bool operator<(const State &lhs, const State &rhs)
{
	return lhs.getID() < rhs.getID();
}

const State &State::operator=(const State &s)
{
	id = s.getID();
	type = s.getType();

	return *this;
}