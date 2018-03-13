#include "TransitionTable.h"

TransitionTable::TransitionTable()
{

}

TransitionTable::~TransitionTable()
{

}

void TransitionTable::add(const std::vector<State> &currentStates, char input, const std::vector<State> &nextStates)
{

}

std::vector<State> TransitionTable::nextStates(const std::vector<State> &currentStates, char input) const
{
	return std::vector<State>();
}

std::ostream& operator<<(std::ostream& out, const TransitionTable &transitionTable)
{
	return out;
}

std::istream& operator>>(std::istream& in, TransitionTable &transitionTable)
{
	return in;
}
