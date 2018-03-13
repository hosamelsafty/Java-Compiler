#ifndef TransitionTable_H
#define TransitionTable_H

#include <string>
#include <vector>
#include <iostream>

#include "State.h"

class TransitionTable
{
public:
    TransitionTable();
    ~TransitionTable();

    void add(const std::vector<State> &currentStates, char input, const std::vector<State> &nextStates);

    std::vector<State> nextStates(const std::vector<State> &currentStates, char input) const;

private:

};

ostream& operator<<(ostream& out, const Transitiontable &transitionTable);
istream& operator>>(istream& in, Transitiontable &transitionTable);

#endif // TransitionTable_H
