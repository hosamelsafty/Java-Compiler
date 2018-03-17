#include "convertNFAToDFA.h"
#include <queue>

DFATransitionTable convertNFAToDFA(const NFATransitionTable &nfa)
{
    using namespace std;

	map<set<State>,State> map;
    queue<set<State>> workingSet;
    workingSet.push(nfa.getStartingSet());

    DFATransitionTable DFA;
    int newStateId = 0;
    State  startState(newStateId++);
    startState.setType(STARTING);
    map[nfa.getStartingSet()] = startState;
    while(!workingSet.empty())
    {
        set<State> s = workingSet.front();
        workingSet.pop();
        for (auto& pair : nfa.getMapping(s))
        {
            if(map.find(pair.second) == map.end()){
                State newState(newStateId++);
                map[pair.second] = newState;
                workingSet.push(pair.second);
            }
            DFA.add(map[s],pair.first,map[pair.second]);
        }
    }
	return DFA;
}
