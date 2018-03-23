#ifndef DFATransitionTable_H
#define DFATransitionTable_H

#include <string>
#include <set>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "State.h"

class DFATransitionTable {
public:
    DFATransitionTable();
    DFATransitionTable(const DFATransitionTable &);
    ~DFATransitionTable();

    void add(const State &, char input, const State &);

    State nextState(const State &, char input) const;
    bool checkTransition (const State &, char input) const;

    std::vector<State> getStates() const;
    std::map<char,State> getMapping(const State&) const;
    // edited by Omar Kassem
    void setStartingState(const State &state);

	void setAcceptingStates(const std::set<State> &states);
	void addAcceptingState(const State &state);

	State getStartingState() const;
	std::set<State> getAcceptingStates() const;

private:
    struct impl;
    std::unique_ptr<impl> m_d;
    friend std::ostream& operator << (std::ostream& out, const DFATransitionTable &transitionTable);
    friend std::istream& operator >> (std::istream& in, DFATransitionTable &transitionTable);
};

std::ostream& operator<<(std::ostream& out, const DFATransitionTable &transitionTable);
std::istream& operator>>(std::istream& in, DFATransitionTable &transitionTable);

#endif // DFATransitionTable_H
