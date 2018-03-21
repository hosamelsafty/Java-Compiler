#include "NFATransitionTable.h"
#include <algorithm>
#include <iterator>
#include <assert.h>

struct NFATransitionTable::impl
{
	std::vector< Transition > transitions;
	std::map< State, std::set<int> > fromIndex;
	std::map< State, std::set<int> > toIndex;

	std::set<State> startingStates;
	std::set<State> endingStates;
};

NFATransitionTable::NFATransitionTable()
	: m_d(std::make_unique<impl>())
{

}

NFATransitionTable::NFATransitionTable(const NFATransitionTable & t)
	: m_d(std::make_unique<impl>())
{
	// TODO
}

NFATransitionTable::~NFATransitionTable()
{

}

const NFATransitionTable & NFATransitionTable::operator=(const NFATransitionTable &nfa)
{
	// TODO
}

void NFATransitionTable::setTransition(const State &fromState, NFATransitionTable::Input input, const State &toState)
{
	std::set<int> fromIndicies = m_d->fromIndex[fromState];
	std::set<int> fromIndicies = m_d->toIndex[toState];
	std::set<int> possibleCollision;
	set_intersection(fromIndicies.begin(), fromIndicies.end(), fromIndicies.begin(), fromIndicies.end(),
		std::inserter(possibleCollision, possibleCollision.begin()));

	for (int i : possibleCollision)
	{
		if (std::get<1>(m_d->transitions[i]) == input)
		{
			// No need to add the same transition again
			return;
		}
	}

	// That transition is not found. Add it.
	m_d->transitions.push_back(Transition(fromState, input, toState));
	int index = m_d->transitions.size() - 1;
	m_d->fromIndex[fromState].insert(index);
	m_d->toIndex[toState].insert(index);
}

std::vector<NFATransitionTable::Transition> NFATransitionTable::getAllTransitions() const
{
	return m_d->transitions;
}

std::set<State> NFATransitionTable::epsClosure(const State &state) const
{

}
std::set<State> NFATransitionTable::epsClosure(const std::set<State> &states) const
{

}
std::set<State> NFATransitionTable::move(const std::set<State> &states, char input) const
{

}

void NFATransitionTable::setStartingStates(const std::set<State> &states)
{
	m_d->startingStates = states;
}

void NFATransitionTable::addStartingState(const State &state)
{
	m_d->startingStates.insert(state);
}

void NFATransitionTable::removeStartingState(const State &state)
{
	m_d->startingStates.erase(state);
}

void NFATransitionTable::setAcceptingStates(const std::set<State> &states)
{
	m_d->endingStates = states;
}

void NFATransitionTable::addAcceptingStates(const State &state)
{
	m_d->endingStates.insert(state);
}

void NFATransitionTable::removeAcceptingStates(const State &state)
{
	m_d->endingStates.erase(state);
}

std::set<State> NFATransitionTable::getStartingStates() const
{
	return m_d->startingStates;
}

std::set<State> NFATransitionTable::getAcceptingStates() const
{
	return m_d->endingStates;
}

NFATransitionTable NFATransitionTable::opUnion(const NFATransitionTable &rhs) const
{
	NFATransitionTable result;

	// Depending on the uniqueness of State we will add the states from *this and rhs to result.

	// TODO Add all transition of *this to result
	
	// TODO Add all transition of rhs to result

	// TODO Create resultStartingState

	// TODO Add to result: transitions from resultStartingState to all startingStates of *this 

	// TODO Add to result: transitions from resultStartingState to all startingStates of rhs

	// TODO Create resultEndingState

	// TODO Add to result: transitions from all endingStates of *this to resultEndingState.

	// TODO Add to result: transitions from all endingStates of rhs to resultEndingState.

	return result;
}

NFATransitionTable NFATransitionTable::opConcat(const NFATransitionTable &rhs) const
{
	// *this must have one endingState and rhs must have one starting state.
	assert(this->getAcceptingStates().size() == 1);
	assert(rhs.getAcceptingStates().size() == 1);

	NFATransitionTable result;

	// Depending on the uniqueness of State we will add the states from *this and rhs to result.

	// TODO Add all transition of *this to result

	// TODO Add all transition of rhs to result.
	// Special case for transitions starting at the startingState of rhs.
	// The from part of these transitions will be replaced by the endingState *this when being added to result.

	// TODO Set startingState of result to be the starting state of *this.

	// TODO Set endingState of result to be the ending state of rhs.

	return result;
}

NFATransitionTable NFATransitionTable::opPlus() const
{

}

NFATransitionTable NFATransitionTable::opStar() const
{

}
