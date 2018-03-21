#ifndef TransitionTable_H
#define TransitionTable_H

#include <string>
#include <set>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "State.h"

class NFATransitionTable
{
public:
    NFATransitionTable();
    NFATransitionTable(const NFATransitionTable &);
    ~NFATransitionTable();

    void add(const std::set<State> &currentStates, char input, const std::set<State> &nextStates);
    std::set<State> nextStates(const std::set<State> &currentStates, char input) const;
	std::map<char, std::set<State> > getMapping(const std::set<State> &currentStates) const;
	std::set<State> getStartingSet() const;

private:
    std::set<State> startingSet;
	struct impl;
	std::unique_ptr<impl> m_d;
};

#endif // NFATransitionTable_H
