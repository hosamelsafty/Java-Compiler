#ifndef TransitionTable_H
#define TransitionTable_H

#include <string>
#include <set>
#include <iostream>
#include <memory>

#include "State.h"

class TransitionTable
{
public:
    TransitionTable();
	TransitionTable(const TransitionTable &);
    ~TransitionTable();

    void add(const std::set<State> &currentStates, char input, const std::set<State> &nextStates);

    std::set<State> nextStates(const std::set<State> &currentStates, char input) const;

private:
	struct impl;
	std::unique_ptr<impl> m_d;
	friend std::ostream& operator<<(std::ostream& out, const TransitionTable &transitionTable);
};

std::ostream& operator<<(std::ostream& out, const TransitionTable &transitionTable);
std::istream& operator>>(std::istream& in, TransitionTable &transitionTable);

#endif // TransitionTable_H
