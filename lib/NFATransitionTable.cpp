#include "NFATransitionTable.h"

struct NFATransitionTable::impl
{
	std::map < std::set<State>, std::map<char, std::set<State> > > table;
};

NFATransitionTable::NFATransitionTable()
	: m_d(std::make_unique<impl>())
{

}

NFATransitionTable::NFATransitionTable(const NFATransitionTable & t)
	: m_d(std::make_unique<impl>())
{
	m_d->table = t.m_d->table;
}

NFATransitionTable::~NFATransitionTable()
{

}

void NFATransitionTable::add(const std::set<State> &currentStates, char input, const std::set<State> &nextStates)
{
	m_d->table[currentStates][input] = nextStates;
}

std::set<State> NFATransitionTable::nextStates(const std::set<State> &currentStates, char input) const
{
	return m_d->table[currentStates][input];
}


std::map<char, std::set<State> > NFATransitionTable::getMapping(const std::set<State> &currentStates) const
{
    return m_d->table[currentStates];
};

std::set<State> NFATransitionTable::getStartingSet() const
{
    return  startingSet;
}
