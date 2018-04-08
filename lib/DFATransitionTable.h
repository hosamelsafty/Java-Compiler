#ifndef DFATransitionTable_H
#define DFATransitionTable_H

#include <string>
#include <set>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "State.h"

class DFATransitionTable
{
public:
    DFATransitionTable();
    DFATransitionTable(const DFATransitionTable &);
    ~DFATransitionTable();


    void storeState(const State &s);
    State getState(StateId stateId) const;
    std::map<StateId, State> getStates() const;
    
    void setTransition(StateId fromId, char input, StateId toId);

    StateId move(StateId stateId, char input) const;
    bool hasTransition(StateId stateId, char input) const;

    void setStartingState(StateId stateId);
    StateId getStartingState() const;

    void addAcceptingState(StateId stateId);
    void setAcceptingStates(const std::set<StateId> &states);
    std::set<StateId> getAcceptingStateIds() const;

    bool isAcceptingState(StateId stateId) const;











    //void add(const State &, char input, const State &);

    //State nextState(const State &, char input) const;
    //bool checkTransition(const State &, char input) const;

    //std::vector<State> getStates() const;
    //std::map<char, State> getMapping(const State&) const;
    //// edited by Omar Kassem
    //void setStartingState(const State &state);

    //void setAcceptingStates(const std::set<State> &states);
    //void addAcceptingState(const State &state);

    //bool isAcceptingState(const State &state) const;
    //State getStartingState() const;
    //std::set<State> getAcceptingStates() const;

private:
    struct impl;
    std::unique_ptr<impl> m_d;
    friend std::ostream& operator << (std::ostream& out, const DFATransitionTable &transitionTable);
    friend std::istream& operator >> (std::istream& in, DFATransitionTable &transitionTable);
};

std::ostream& operator<<(std::ostream& out, const DFATransitionTable &transitionTable);
std::istream& operator >> (std::istream& in, DFATransitionTable &transitionTable);

#endif // DFATransitionTable_H
