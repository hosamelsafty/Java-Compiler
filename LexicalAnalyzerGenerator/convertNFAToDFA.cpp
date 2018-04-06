#include "convertNFAToDFA.h"
#include "lib/AcceptedTokenMap.h"
#include <queue>

using namespace std;

/* Returns a new DFA from an input NFA */
DFATransitionTable convertNFAToDFA(const NFATransitionTable &nfa)
{
    set<State> startingSet = nfa.epsClosure(nfa.getStartingStates());

    map<set<State>, State> map;
    queue<set<State>> workingSet;
    workingSet.push(startingSet);

    int newStateId = 0;
    DFATransitionTable DFA;
    State startState(newStateId++);
    startState.setType(STARTING);
    if (nfa.isAcceptingSet(startingSet))
    {
        startState.setType(ACCEPTING);
        DFA.addAcceptingState(startState);
        string tkn = AcceptedTokenMap::getNFAMapping(startingSet);
        AcceptedTokenMap::addDFAMapping(startState, tkn);
    }
    DFA.setStartingState(startState);
    map[startingSet] = startState;
    while (!workingSet.empty())
    {
        set<State> s = workingSet.front();
        workingSet.pop();
        for (char input : nfa.transitionAlphabet(s))
        {
            // t = e-closure(move(s,I))
            set<State> t = nfa.epsClosure(nfa.move(s, input));
            // if t is not in map
            if (map.find(t) == map.end())
            { // A new set is found
// make a new DFA representative state of the NFA set
                State newState(newStateId++);
                if (nfa.isAcceptingSet(t))
                {
                    newState.setType(ACCEPTING);
                    DFA.addAcceptingState(newState);
                    string tkn = AcceptedTokenMap::getNFAMapping(t);
                    AcceptedTokenMap::addDFAMapping(newState, tkn);
                }
                map[t] = newState;
                workingSet.push(t);
            }
            // DFA[s,I] = map[t]
            DFA.add(map[s], input, map[t]);
        }
    }
    return DFA;
}
