#include "convertNFAToDFA.h"
#include <queue>

using namespace std;

/* returns true if the set contains an accepting state */
bool isAccepting(std::set<State> s){
    for(auto& st : s) {
        if(st.getType() == ACCEPTING)
            return true;
    }
    return false;
}

/* Returns a new DFA from an input NFA */
DFATransitionTable convertNFAToDFA(const NFATransitionTable &nfa)
{
    map<set<State>,State> map;
    queue<set<State>> workingSet;
    workingSet.push(nfa.getStartingStates());
    DFATransitionTable DFA;
    int newStateId = 0;
    State startState(newStateId++);
    startState.setType(STARTING);
    map[nfa.getStartingStates()] = startState;
    /*while(!workingSet.empty())
    {
        set<State> s = workingSet.front();
        workingSet.pop();
        for (auto& pair : nfa.getMapping(s))
        {
            if(map.find(pair.second) == map.end()){ // A new set is found
                // make a new DFA representative state of the NFA set
                State newState(newStateId++);
                if(isAccepting(pair.second))
                    newState.setType(ACCEPTING);
                map[pair.second] = newState;
                workingSet.push(pair.second);
            }
            DFA.add(map[s],pair.first,map[pair.second]);
        }
    }*/
    return DFA;
}