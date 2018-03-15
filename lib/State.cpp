#include "State.h"

State::State()
{

}

State::State(const std::string name)
	: name(name)
{

}

bool operator<(const State &lhs, const State &rhs)
{
	return lhs.name < rhs.name;
}