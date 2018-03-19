#include "convertNFAToDFA.h"
#include <queue>



bool isAcceptance(std::set<State> s){
    for(auto& st : s) {
        if(st.getType() == ACCEPTING)
            return true;
    }
    return false;
}

DFATransitionTable convertNFAToDFA(const NFATransitionTable &nfa)
{
    using namespace std;

	map<set<State>,State> map;
    queue<set<State>> workingSet;
    workingSet.push(nfa.getStartingSet());

    int newStateId = 0;
    State  startState(newStateId++);
    startState.setType(STARTING);
    map[nfa.getStartingSet()] = startState;
    DFATransitionTable DFA(startState);
    while(!workingSet.empty())
    {
        set<State> s = workingSet.front();
        workingSet.pop();
        for (auto& pair : nfa.getMapping(s))
        {
            if(map.find(pair.second) == map.end()){
                State newState(newStateId++);
                if(isAcceptance(pair.second))
                    newState.setType(ACCEPTING);
                map[pair.second] = newState;
                workingSet.push(pair.second);
            }
            DFA.add(map[s],pair.first,map[pair.second]);
        }
    }
	return DFA;
}
