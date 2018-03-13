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

std::ostream& operator<<(std::ostream& out, const TransitionTable &transitionTable);
std::istream& operator>>(std::istream& in, TransitionTable &transitionTable);

#endif // TransitionTable_H
