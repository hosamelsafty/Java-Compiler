#include "minimizeDFA.h"
#include "convertNFAToDFA.h"
#include "convertRulesToNFA.h"
#include "writeTransitionTable.h"

#include "lib/NFATransitionTable.h"

#include <string>

int main(int argc, char** argv)
{
    using namespace std;

    // TODO Read Rules file and convert to NFA
    // input: filename
    // output: TransitionTable
    //TransitionTable nfa = convertRulesToNFA(rulesFilename);

    // TODO Convert NFA to DFA
    // input: TransitionTable
    // output: TransitionTable
	NFATransitionTable nfa;
    State q9(9);
    q9.setType(ACCEPTING);
    nfa.startingSet = set<State>{State(0)};
    set<State> s1 = set<State>{State(1),State(2),State(3),State(4),State(6),q9};
    set<State> s2 = set<State>{State(5),State(8),State(6),State(3),State(4),q9};
    set<State> s3 = set<State>{State(7),State(8),State(6),State(3),State(4),q9};
    nfa.add(nfa.startingSet,'a',s1);
    nfa.add(s1,'b',s2);
    nfa.add(s1,'c',s3);

    nfa.add(s2,'b',s2);
    nfa.add(s2,'c',s3);

    nfa.add(s3,'b',s2);
    nfa.add(s3,'c',s3);

    DFATransitionTable dfa = convertNFAToDFA(nfa);
    for(auto&st:dfa.getStates()){
        cout << "State: " << st.getID() << " , Type: " << st.getType() << endl ;
        for(auto& pair : dfa.getMapping(st)){
            cout << "under: " << pair.first << " , it goes to: " << pair.second.getID() << endl ;
        }
    }

    // TODO minimize DFA
    // input: TransitionTable
    // output: TransitionTable
    //DFATransitionTable minDFA= minimizeDFA(dfa);

	// Examples
	//minDFA.add(std::set<State>{State("asd"), State("qwe")}, 'a', std::set<State>{State("asd"), State("qwe")});
	//minDFA.add(std::set<State>{State("asd"), State("qwe")}, 'b', std::set<State>{State("asd"), State("qwe")});

	//minDFA.add(std::set<State>{State("toot")}, 'a', std::set<State>{State("asd"), State("qwe")});
	//minDFA.add(std::set<State>{State("toot")}, 'b', std::set<State>{State("asd"), State("qwe")});

    // TODO write TransitionTable to file
    // input: TransitionTable, filename
    // file containing TransitionTable with proper format.
	//std::string outputFilename = "tt.json";
    //writeTransitionTable(minDFA, outputFilename);

    return 0;
}
