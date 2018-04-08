#include "minimizeDFA.h"
#include "convertNFAToDFA.h"
#include "convertRulesToNFA.h"
#include "writeTransitionTable.h"

#include "lib/NFATransitionTable.h"

#include <string>
#include <fstream>

int main(int argc, char** argv)
{
    using namespace std;

    // Skip the executable name
    argc--; argv++;

    if (argc == 0)
    {
        cout << "Please insert the path for a rules file on the command line. Example: LexicalAnalyzerGenerator ./rules.txt";
        return 0;
    }

    NFATransitionTable nfa = convertRulesToNFA(argv[0]);

    DFATransitionTable dfa1 = convertNFAToDFA(nfa);

    //DFATransitionTable minDFA = minimizeDFA(dfa1);

    writeTransitionTable(dfa1, "dfa.json");

    cout << endl << "Transition table written to dfa.json" << endl;

    return 0;
}


/***** DRAFT *****/

//for (State s:dfa1.getStates()) {
//    cout << "StateID:" << s.getID() << " , type:" << s.getType() << endl;
//    for(auto& pair: dfa1.getMapping(s)){
//        cout << "Under char '" << pair.first<< "' , it goes to stateID:" << pair.second.getID()<<endl;
//    }
//}


//// This is Tested ##
//NFATransitionTable nfa = convertRulesToNFA("C:/Users/win8.1/Desktop/compiler/javacompiler/domx.txt");
//cout << "size:" << nfa.getStartingStates().size() << endl;
//set<State> cl = nfa.epsClosure(nfa.getStartingStates());
//cout << "size closure:" << cl.size()<<endl;


//NFATransitionTable tr;
//const char EPS ='\17';
//State s0(0);
//State s1(1);
//State s2(2);
//State s3(3);
//State s4(4);
//State s5(5);
//State s6(6);
//tr.setStartingStates(set<State>({s0}));
//tr.setAcceptingStates(set<State>({s6}));
//tr.setTransition(s0,EPS,s1);
//tr.setTransition(s0,EPS,s2);
//tr.setTransition(s1,EPS,s3);
//tr.setTransition(s3,EPS,s4);
//tr.setTransition(s4,'b',s6);
//tr.setTransition(s2,'a',s5);
//tr.setTransition(s5,EPS,s6);
//tr.setTransition(s1,'c',s6);
//tr.setTransition(s2,EPS,s6);


//DFATransitionTable dfa = convertNFAToDFA(tr);
//for (State s:dfa.getStates()) {
//    cout << "StateID:" << s.getID() << " , type:" << s.getType() << endl;
//    for(auto& pair: dfa.getMapping(s)){
//        cout << "Under char '" << pair.first<< "' , it goes to stateID:" << pair.second.getID()<<endl;
//    }
//}


//DFATransitionTable dfaTest;
//dfaTest.add(State(1), 'a', State(2));
//dfaTest.add(State(2), 'b', State(3));
//dfaTest.add(State(1), 'b', State(2));
//dfaTest.addAcceptingState(State(2));
//dfaTest.setStartingState(State(1));


//writeTransitionTable(dfaTest, "dfa.json");


//DFATransitionTable dfaTest2;
//std::ifstream inFile;
//inFile.open("dfa.json");
//inFile >> dfaTest2;
