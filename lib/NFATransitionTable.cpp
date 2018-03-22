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

std::vector<NFATransitionTable::Transition> NFATransitionTable::getAllTransitions() const
{
	return m_d->transitions;
}

std::set<State> NFATransitionTable::impl::directClosure(const State &state, char input) const
{
	std::set<State> states;

	std::set<int> fromIndicies = fromIndex[state];

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
	result.getAllTransitions().insert(result.getAllTransitions().end(),
									  (*this).getAllTransitions().begin(), (*this).getAllTransitions().end());

	
	// TODO Add all transition of rhs to result
	result.getAllTransitions().insert(result.getAllTransitions().end(),
									  rhs.getAllTransitions().begin(), rhs.getAllTransitions().end());

	// TODO Create resultStartingState
	State startState(State::newID());
	result.setStartingStates(std::set<State>{startState});

	// TODO Add to result: transitions from resultStartingState to all startingStates of *this 
	for (auto& elem:(*this).getStartingStates()){
		result.setTransition(startState,'\0',elem);
	}
	// TODO Add to result: transitions from resultStartingState to all startingStates of rhs
	for (auto& elem: rhs.getStartingStates()){
		result.setTransition(startState,'\0',elem);
	}
	// TODO Create resultEndingState
	State endState(State::newID());
	result.setAcceptingStates(std::set<State>{endState});
	// TODO Add to result: transitions from all endingStates of *this to resultEndingState.
	for (auto& elem:(*this).getAcceptingStates()){
		result.setTransition(endState,'\0',elem);
	}
	// TODO Add to result: transitions from all endingStates of rhs to resultEndingState.
	for (auto& elem: rhs.getAcceptingStates()){
		result.setTransition(elem,'\0',endState);
	}
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
	result.getAllTransitions().insert(result.getAllTransitions().end(),
									  (*this).getAllTransitions().begin(), (*this).getAllTransitions().end());


	// TODO Add all transition of rhs to result
	result.getAllTransitions().insert(result.getAllTransitions().end(),
									  rhs.getAllTransitions().begin(), rhs.getAllTransitions().end());
	tempStartState=*((*this).getStartingStates().begin());
	tempEndState=*((*this).getAcceptingStates().begin());
	// TODO Add all transition of *this to result
	result.getAllTransitions().insert(result.getAllTransitions().end(),
									  (*this).getAllTransitions().begin(), (*this).getAllTransitions().end());
	result.setTransition(tempEndState,'\0',tempStartState);
	// Special case for transitions starting at the startingState of rhs.
	// The from part of these transitions will be replaced by the endingState *this when being added to result.
	State startState(State::newID());
	result.setStartingStates(std::set<State>{startState});

	// TODO Set startingState of result to be the starting state of *this.
	for (auto& elem:(*this).getStartingStates()){
		result.setTransition(startState,'\0',elem);
	}
	State endState(State::newID());
	result.setAcceptingStates(std::set<State>{endState});

	// TODO Set endingState of result to be the ending state of rhs.
	for (auto& elem: rhs.getAcceptingStates()){
		result.setTransition(elem,'\0',endState);
	}
	return result;
}

NFATransitionTable NFATransitionTable::opPlus() const
{	NFATransitionTable result;
	NFATransitionTable starNFA;
	// TODO Create resultStartingState
	State startState(State::newID());
	result.setStartingStates(std::set<State>{startState});
	// TODO Add to result: transitions from resultStartingState to all startingStates of *this
	for (auto& elem:(*this).getStartingStates()){
		result.setTransition(startState,'\0',elem);
	}
	// TODO Create resultEndingState
	State endState(State::newID());
	result.setAcceptingStates(std::set<State>{endState});

	for (auto& elem:(*this).getAcceptingStates()){
		result.setTransition(startState,'\0',elem);
	}

	return result.opConcat((*this).opStar());

}

NFATransitionTable NFATransitionTable::opStar() const
{
	NFATransitionTable result;

	State tempStartState(State::newID());
	State tempEndState(State::newID());
	tempStartState=*((*this).getStartingStates().begin());
	tempEndState=*((*this).getAcceptingStates().begin());
	// TODO Add all transition of *this to result
	result.getAllTransitions().insert(result.getAllTransitions().end(),
									  (*this).getAllTransitions().begin(), (*this).getAllTransitions().end());
	result.setTransition(tempEndState,'\0',tempStartState);
	// TODO Create resultStartingState
	State startState(State::newID());
	result.setStartingStates(std::set<State>{startState});
	// TODO Add to result: transitions from resultStartingState to all startingStates of *this
	for (auto& elem:(*this).getStartingStates()){
		result.setTransition(startState,'\0',elem);
	}
	// TODO Create resultEndingState
	State endState(State::newID());
	result.setAcceptingStates(std::set<State>{endState});
	// TODO Add to result: transitions from all endingStates of *this to resultEndingState.
	for (auto& elem:(*this).getAcceptingStates()){
		result.setTransition(elem,'\0',endState);
	}
	result.setTransition(startState,'\0',endState);
	return result;
}
