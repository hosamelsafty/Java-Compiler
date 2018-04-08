#include "convertNFAToDFA.h"
#include "lib/AcceptedTokenMap.h"
#include <queue>
#include <iterator>
#include <assert.h>

using namespace std;

DFATransitionTable convertNFAToDFA(const NFATransitionTable &nfa)
{
    DFATransitionTable dfa;

    // map between NFA set of states and DFA State
    map<set<State>, StateId> Dstates;
    std::vector<set<State>> toBeProcessed;

    set<State> startClosure = nfa.epsClosure2(nfa.getStartingStates());
    State s;
    dfa.storeState(s);
    Dstates[startClosure] = s.getID();
    toBeProcessed.push_back(startClosure);

    dfa.setStartingState(Dstates[startClosure]);

    const set<State> nfaAcceptingStates = nfa.getAcceptingStates();

    while (toBeProcessed.size())
    {
        set<State> workingSet = *toBeProcessed.begin();
        StateId fromState = Dstates[workingSet];

        set<char> alphabet = nfa.transitionAlphabet2(workingSet);

        for (char input : alphabet)
        {
            set<State> states = nfa.epsClosure(nfa.move(workingSet, input));
            auto dStateIt = Dstates.find(states);
            if (dStateIt == Dstates.end())
            {
                State s;
                dfa.storeState(s);
                Dstates[states] = s.getID();

                vector<State> acceptingStates;
                set_intersection(nfaAcceptingStates.begin(), nfaAcceptingStates.end(), states.begin(), states.end(),
                    std::inserter(acceptingStates, acceptingStates.begin()));

                if (acceptingStates.size())
                {
                    // Take the one with the highest priority
                    auto chosenAcceptingState = std::max_element(acceptingStates.begin(), acceptingStates.end(),
                        [](const State &rhs, const State &lhs) {
                            return rhs.getPriority() < lhs.getPriority();
                    });

                    State acceptingState = *chosenAcceptingState;
                    assert(acceptingState.getTokenType().size());

                    s.setTokenType(acceptingState.getTokenType());
                    dfa.storeState(s);

                    dfa.addAcceptingState(s.getID());
                }

                toBeProcessed.push_back(states);
            }

            StateId toState = Dstates[states];
            dfa.setTransition(fromState, input, toState);
        }

        toBeProcessed.erase(toBeProcessed.begin());
    }

    return dfa;
}

//
///* Returns a new DFA from an input NFA */
//DFATransitionTable convertNFAToDFA2(const NFATransitionTable &nfa)
//{
//    set<State> startingSet = nfa.epsClosure(nfa.getStartingStates());
//
//    map<set<State>, State> map;
//    queue<set<State>> workingSet;
//    workingSet.push(startingSet);
//
//    int newStateId = 0;
//    DFATransitionTable DFA;
//    State startState(newStateId++);
//    startState.setType(STARTING);
//    if (nfa.isAcceptingSet(startingSet))
//    {
//        startState.setType(ACCEPTING);
//        DFA.addAcceptingState(startState);
//        string tkn = AcceptedTokenMap::getNFAMapping(startingSet);
//        AcceptedTokenMap::addDFAMapping(startState, tkn);
//    }
//
//    DFA.setStartingState(startState);
//    map[startingSet] = startState;
//    while (!workingSet.empty())
//    {
//        set<State> s = workingSet.front();
//        workingSet.pop();
//        for (char input : nfa.transitionAlphabet(s))
//        {
//            // t = e-closure(move(s,I))
//            set<State> t = nfa.epsClosure(nfa.move(s, input));
//            // if t is not in map
//            if (map.find(t) == map.end())
//            { // A new set is found
//// make a new DFA representative state of the NFA set
//                State newState(newStateId++);
//                if (nfa.isAcceptingSet(t))
//                {
//                    newState.setType(ACCEPTING);
//                    DFA.addAcceptingState(newState);
//                    string tkn = AcceptedTokenMap::getNFAMapping(t);
//                    AcceptedTokenMap::addDFAMapping(newState, tkn);
//                }
//                map[t] = newState;
//                workingSet.push(t);
//            }
//            // DFA[s,I] = map[t]
//            DFA.add(map[s], input, map[t]);
//        }
//    }
//    return DFA;
//}
