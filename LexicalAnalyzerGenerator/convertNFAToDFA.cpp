#include "convertNFAToDFA.h"
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

    set<State> startClosure = nfa.epsClosure(nfa.getStartingStates());
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

        set<char> alphabet = nfa.transitionAlphabet(workingSet);

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
