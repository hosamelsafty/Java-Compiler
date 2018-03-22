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

	std::set<State> directClosure(const State &state, char input) const;
};


NFATransitionTable::NFATransitionTable()
	: m_d(std::make_unique<impl>())
{

}

NFATransitionTable::NFATransitionTable(const NFATransitionTable & nfa)
	: m_d(std::make_unique<impl>())
{
	m_d->transitions = nfa.m_d->transitions;
	m_d->fromIndex = nfa.m_d->fromIndex;
	m_d->toIndex = nfa.m_d->toIndex;
	m_d->startingStates = nfa.m_d->startingStates;
	m_d->endingStates = nfa.m_d->endingStates;
}

NFATransitionTable::~NFATransitionTable()
{

}

const NFATransitionTable & NFATransitionTable::operator=(const NFATransitionTable &nfa)
{
	m_d->transitions = nfa.m_d->transitions;
	m_d->fromIndex = nfa.m_d->fromIndex;
	m_d->toIndex = nfa.m_d->toIndex;
	m_d->startingStates = nfa.m_d->startingStates;
	m_d->endingStates = nfa.m_d->endingStates;

	return *this;
}

void NFATransitionTable::setTransition(const State &fromState, NFATransitionTable::Input input, const State &toState)
{
	std::set<int> fromIndicies = m_d->fromIndex[fromState];
	std::set<int> toIndicies = m_d->toIndex[toState];
	std::set<int> possibleCollision;
	set_intersection(fromIndicies.begin(), fromIndicies.end(), toIndicies.begin(), toIndicies.end(),
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

void NFATransitionTable::setTransition(const Transition &transition)
{
	setTransition(std::get<0>(transition), std::get<1>(transition), std::get<2>(transition));
}

std::vector<NFATransitionTable::Transition> NFATransitionTable::getAllTransitions() const
{
	return m_d->transitions;
}

std::set<State> NFATransitionTable::impl::directClosure(const State &state, char input) const
{
	std::set<State> states;

	std::set<int> fromIndicies = fromIndex.at(state);

	for (int i : fromIndicies)
	{
		if (std::get<1>(transitions[i]) == input)
		{
			states.insert(std::get<2>(transitions[i]));
		}
	}
	return states;
}

std::set<State> NFATransitionTable::epsClosure(const State &state) const
{
	std::set<State> resultColsure;
	resultColsure.insert(state);

	std::set<State> toBeProcessed;
	std::set<State> doneProcessing;

	toBeProcessed.insert(state);

	while (toBeProcessed.size())
	{
		std::set<State> directClosure = m_d->directClosure(*toBeProcessed.begin(), EPS);
		resultColsure.insert(directClosure.begin(), directClosure.end());
		
		doneProcessing.insert(*toBeProcessed.begin());
		toBeProcessed.erase(*toBeProcessed.begin());

		std::set<State> newInClosure;

		std::set_difference(directClosure.begin(), directClosure.end(), doneProcessing.begin(), doneProcessing.end(),
			std::inserter(newInClosure, newInClosure.begin()));

		if (newInClosure.size())
		{
			toBeProcessed.insert(newInClosure.begin(), newInClosure.end());
		}
	}

	return resultColsure;
}

std::set<State> NFATransitionTable::epsClosure(const std::set<State> &states) const
{
	std::set<State> resultClosure;

	for (auto && state : states)
	{
		// This is not efficient but correct
		std::set<State> closure = epsClosure(state);
		resultClosure.insert(closure.begin(), closure.end());
	}

	return resultClosure;
}

std::set<State> NFATransitionTable::move(const std::set<State> &states, char input) const
{
	std::set<State> directClosureOfinput;

	for (auto && state : states)
	{
		std::set<State> closure = m_d->directClosure(state, input);
		directClosureOfinput.insert(closure.begin(), closure.end());
	}

	return epsClosure(directClosureOfinput);

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
	for (auto && transition : m_d->transitions)
	{
		result.setTransition(transition);
	}

	// TODO Add all transition of rhs to result
	for (auto && transition : rhs.m_d->transitions)
	{
		result.setTransition(transition);
	}

	// TODO Create resultStartingState
	State startState(State::newID());
	result.setStartingStates(std::set<State>{startState});

	// TODO Add to result: transitions from resultStartingState to all startingStates of *this 
	for (auto& state : m_d->startingStates)
	{
		result.setTransition(startState, EPS, state);
	}

	// TODO Add to result: transitions from resultStartingState to all startingStates of rhs
	for (auto& state : rhs.m_d->startingStates)
	{
		result.setTransition(startState, EPS, state);
	}

	// TODO Create resultEndingState
	State endState(State::newID());
	result.setAcceptingStates(std::set<State>{endState});

	// TODO Add to result: transitions from all endingStates of *this to resultEndingState.
	for (auto& state : m_d->endingStates)
	{
		result.setTransition(state, EPS, endState);
	}

	// TODO Add to result: transitions from all endingStates of rhs to resultEndingState.
	for (auto& state : rhs.m_d->endingStates)
	{
		result.setTransition(state, EPS, endState);
	}

	return result;
}

NFATransitionTable NFATransitionTable::opConcat(const NFATransitionTable &rhs) const
{
	// *this must have one endingState and rhs must have one starting state.
	assert(this->getAcceptingStates().size() == 1);
	assert(rhs.getStartingStates().size() == 1);

	NFATransitionTable result;

	// Depending on the uniqueness of State we will add the states from *this and rhs to result.

	// TODO Add all transition of *this to result
	for (auto && transition : m_d->transitions)
	{
		result.setTransition(transition);
	}

	// TODO Add all transition of rhs to result.
	// Special case for transitions starting at the startingState of rhs.
	// The from part of these transitions will be replaced by the endingState *this when being added to result.
	State endingStateThis = *m_d->endingStates.begin();
	State startingStateRHS = *rhs.m_d->startingStates.begin();
	for (auto && transition : rhs.m_d->transitions)
	{
		if (std::get<0>(transition) == startingStateRHS)
		{
			result.setTransition(Transition(endingStateThis, std::get<1>(transition), std::get<2>(transition)));
		}
		else
		{
			result.setTransition(transition);
		}
	}

	// TODO Set startingState of result to be the starting state of *this.
	result.setStartingStates(m_d->startingStates);
	
	
	// TODO Set endingState of result to be the ending state of rhs.
	result.setAcceptingStates(rhs.m_d->endingStates);

	return result;
}

NFATransitionTable NFATransitionTable::opPlus() const
{
	// *this must have one endingState and rhs must have one starting state.
	assert(m_d->startingStates.size() == 1);
	assert(m_d->endingStates.size() == 1);
	
	NFATransitionTable result = (*this).opConcat((*this).opStar());

	return result;
}

NFATransitionTable NFATransitionTable::opStar() const
{
	// *this must have one endingState and rhs must have one starting state.
	assert(m_d->startingStates.size() == 1);
	assert(m_d->endingStates.size() == 1);

	NFATransitionTable result;
	State startingState(State::newID());
	State endingState(State::newID());

	State startingStateThis = *m_d->startingStates.begin();
	State endingStateThis = *m_d->endingStates.begin();

	// TODO Add all transition of *this to result
	for (auto && transition : m_d->transitions)
	{
		result.setTransition(transition);
	}

	result.setTransition(
		endingStateThis,
		EPS,
		startingStateThis);


	result.setTransition(
		startingState,
		EPS,
		startingStateThis);

	result.setTransition(
		endingStateThis,
		EPS,
		endingState);

	result.setTransition(
		startingState,
		EPS,
		endingState);

	result.addStartingState(startingState);
	result.addAcceptingStates(endingState);

	return result;
}
