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
	typedef char Input;

	// TODO epsilon symbol need to be defined
	static const char EPS;

	typedef std::tuple<State, Input, State> Transition;

    NFATransitionTable();
    NFATransitionTable(const NFATransitionTable &nfa);
    ~NFATransitionTable();

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
