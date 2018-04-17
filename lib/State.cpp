#include "State.h"


State::State() :
		id(-1) {

#include <iostream>
int State::new_id = 0;
State::State(int number)
	: id(number)

	type = REGULAR;
}


State::State(int number) :
		id(number) {
	type = REGULAR;
}

State::State(int number, std::string mT) :
		id(number), matchToken(mT) {
	type = REGULAR;
}

State::State(int number, std::string mT ,Type t ) :
		id(number), matchToken(mT) {
	type = t;
}

void State::setType(Type t) {
	type = t;
}

Type State::getType() const {
	return type;
}


int State::getID() const {
	return id;

bool State::operator==(const State & s) const
{
	return id == s.getID();

}

std::string State::getMatchedToken() const {
	return matchToken;
}

bool operator<(const State &lhs, const State &rhs) {
	return lhs.getID() < rhs.getID();
}


const State &State::operator=(const State &s)
{
	id = s.getID();
	type = s.getType();

	return *this;
}

