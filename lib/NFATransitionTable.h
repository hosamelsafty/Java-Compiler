#ifndef TransitionTable_H
#define TransitionTable_H

#include <string>
#include <set>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <tuple>

#include "State.h"

class NFATransitionTable
{
public:
	// This is better be implemented as std::optiona (C++17) or Boost::optional
	typedef char Input;

	// Epsilon symbol need to be defined
	// (device control 1) This is a control character that is not likely to exist in a file
	static const char EPS = '\17';

	typedef std::tuple<State, Input, State> Transition;

    NFATransitionTable();
    NFATransitionTable(const NFATransitionTable &nfa);
    ~NFATransitionTable();


      void add(const std::set<State> &currentStates, char input, const std::set<State> &nextStates);
    std::set<State> nextStates(const std::set<State> &currentStates, char input) const;
	std::map<char, std::set<State> > getMapping(const std::set<State> &currentStates) const;
	std::set<State> getStartingSet() const;
	 std::set<State> startingSet;
	 std::set<State> endingSet;
	const NFATransitionTable &operator=(const NFATransitionTable &nfa);

	void setTransition(const State &fromState, Input input, const State &toState);

	std::vector<Transition> getAllTransitions() const;

	std::set<State> epsClosure(const State &state) const;
	std::set<State> epsClosure(const std::set<State> &states) const;
	std::set<State> move(const std::set<State> &states, char input) const;

	void setStartingStates(const std::set<State> &states);
	void addStartingState(const State &state);
	void removeStartingState(const State &state);

	void setAcceptingStates(const std::set<State> &states);
	void addAcceptingStates(const State &state);
	void removeAcceptingStates(const State &state);

	std::set<State> getStartingStates() const;
	std::set<State> getAcceptingStates() const;

	NFATransitionTable opUnion(const NFATransitionTable &rhs) const;
	NFATransitionTable opConcat(const NFATransitionTable &rhs) const;
	NFATransitionTable opPlus() const;
	NFATransitionTable opStar() const;


private:
	struct impl;
	std::unique_ptr<impl> m_d;
};

#endif // NFATransitionTable_H
