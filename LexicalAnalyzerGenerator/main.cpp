//#include "minimizeDFA.h"
//#include "convertNFAToDFA.h"
//#include "convertRulesToNFA.h"
//#include "writeTransitionTable.h"
//
//#include "lib/NFATransitionTable.h"
//#include "lib/LexicalAnalyzer.h"
//#include <string>
//#include <sstream>
//
//int main(int argc, char** argv) {
//	using namespace std;
//
//	// This is Tested ##
//    NFATransitionTable nfa = convertRulesToNFA("/home/omar/eclipse-workspace/JavaCompiler/src/LexicalAnalyzerGenerator/rules.txt");
////
////    DFATransitionTable dfa = convertNFAToDFA(nfa);
////
////	DFATransitionTable minDfa = minimizeDFA(dfa);
////
////	std::string outputFilename = "dfa.json";
////	writeTransitionTable(minDfa, outputFilename);
//
//// TODO Read Rules file and convert to NFA
//// input: filename
//// output: TransitionTable
////TransitionTable nfa = convertRulesToNFA(rulesFilename);
//
//// TODO Convert NFA to DFA
//// input: TransitionTable
//// output: TransitionTable
//	/*NFATransitionTable nfa;
//	 State q9(9);
//	 q9.setType(ACCEPTING);
//	 nfa.startingSet = set<State>{State(0)};
//	 set<State> s1 = set<State>{State(1),State(2),State(3),State(4),State(6),q9};
//	 set<State> s2 = set<State>{State(5),State(8),State(6),State(3),State(4),q9};
//	 set<State> s3 = set<State>{State(7),State(8),State(6),State(3),State(4),q9};
//	 nfa.add(nfa.startingSet,'a',s1);
//	 nfa.add(s1,'b',s2);
//	 nfa.add(s1,'c',s3);
//
//	 nfa.add(s2,'b',s2);
//	 nfa.add(s2,'c',s3);
//
//	 nfa.add(s3,'b',s2);
//	 nfa.add(s3,'c',s3);
//
//	 DFATransitionTable dfa = convertNFAToDFA(nfa);
//	 for(auto&st:dfa.getStates()){
//	 cout << "State: " << st.getID() << " , Type: " << st.getType() << endl ;
//	 for(auto& pair : dfa.getMapping(st)){
//	 cout << "under: " << pair.first << " , it goes to: " << pair.second.getID() << endl ;
//	 }
//	 }*/
//	//Rule
////	State s0 = State(0);
////	s0.setType(STARTING);
////	State s1 = State(1);
////	s1.setType(ACCEPTING);
////	State s2 = State(2);
////	State s3 = State(3);
////	State s4 = State(4);
////	DFATransitionTable dfa;
////	dfa.setStartingState(s0);
////	dfa.addAcceptingState(s1);
////	dfa.add(s0, '0', s1);
////	dfa.add(s0, '1', s2);
////	dfa.add(s1, '0', s2);
////	dfa.add(s1, '1', s3);
////	dfa.add(s2, '0', s1);
////	dfa.add(s2, '1', s2);
////	dfa.add(s3, '0', s0);
////	dfa.add(s3, '1', s2);
////	dfa.add(s4, '0', s3);
////	dfa.add(s4, '1', s4);
////	DFATransitionTable min_dfa = minimizeDFA(dfa);
////	for (auto&st : min_dfa.getStates()) {
////		cout << "State: " << st.getID() << " , Type: "
////				<< st.getType() << endl;
////		for (auto& pair : min_dfa.getMapping(st)) {
////			cout << "under: " << pair.first << " , it goes to: "
////					<< pair.second.getID() << endl;
////		}
////	}
////
////	/*small test for lexical.*/
////	istringstream ss;
////	string string1 = "011100100110101110";
////	ss.str(string1);
////	LexicalAnalyzer la(min_dfa, ss);
////	Token* t = la.nextToken();
////	while (t) {
////		cout << "lasttoken >>> " << t->value << " " << t->type
////				<< endl;
////		t = la.nextToken();
////	}
////	ss.clear();
//
//	// TODO minimize DFA
//	// input: TransitionTable
//	// output: TransitionTable
//	//DFATransitionTable minDFA= minimizeDFA(dfa);
//
//	// Examples
//	//minDFA.add(std::set<State>{State("asd"), State("qwe")}, 'a', std::set<State>{State("asd"), State("qwe")});
//	//minDFA.add(std::set<State>{State("asd"), State("qwe")}, 'b', std::set<State>{State("asd"), State("qwe")});
//
//	//minDFA.add(std::set<State>{State("toot")}, 'a', std::set<State>{State("asd"), State("qwe")});
//	//minDFA.add(std::set<State>{State("toot")}, 'b', std::set<State>{State("asd"), State("qwe")});
//
//	// TODO write TransitionTable to file
//	// input: TransitionTable, filename
//	// file containing TransitionTable with proper format.
//	//std::string outputFilename = "tt.json";
//	//writeTransitionTable(minDFA, outputFilename);
//
//	return 0;
//}
#include "minimizeDFA.h"
#include "convertNFAToDFA.h"
#include "convertRulesToNFA.h"
#include "writeTransitionTable.h"
#include "RulesHandler.h"
#include "lib/NFATransitionTable.h"
#include "lib/ErrorLog.h"
#include "lib/LexicalAnalyzer.h"
#include "LexicalAnalyzer/writeErrorLogToFile.h"
#include "LexicalAnalyzer/printTokensToScreen.h"
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    using namespace std;
    // This is Tested ##
    NFATransitionTable nfa = convertRulesToNFA("/home/omar/eclipse-workspace/JavaCompiler/src/LexicalAnalyzerGenerator/regularExpressions.txt");
    DFATransitionTable dfa = convertNFAToDFA(nfa);
    DFATransitionTable min_dfa = minimizeDFA(dfa);
//	for (auto& s : dfa.getAcceptingStates()) {
//		std::cout << "acc state = " << s.getID() << " token = "
//				<< AcceptedTokenMap::getDFAMapping(s) << endl;
//	}
//	for(auto& s:RulesHandler::punc){
//		cout << s << endl;
//	}
    std::string codeFilename = "/home/omar/eclipse-workspace/JavaCompiler/src/LexicalAnalyzer/test_2.txt";
	std::ifstream codeFile;
	// TODO Check for return value
	codeFile.open(codeFilename);
	ErrorLog errorLog;
	LexicalAnalyzer lexicalAnalyzer(min_dfa, codeFile, errorLog);
	writeTransitionTable(min_dfa,"miniDFA.json");
	printTokensToScreen(lexicalAnalyzer);

	// TODO write ErrorLog somewhere (in a file for example)
	// input: ErrorLog, filename
	// output: file containing error messages one per line.
	std::string errorLogFilename = "errorLog.txt";
	writeErrorLogToFile(errorLog, errorLogFilename);
//    for (State s:dfa.getStates()) {
//        cout << "StateID:" << s.getID() << " , type:" << s.getType() << endl;
//        for(auto& pair: dfa.getMapping(s)){
//            cout << "Under char '" << pair.first<< "' , it goes to stateID:" << pair.second.getID()<<endl;
//        }
//    }

    cout << "-------------------------------------------" << endl;

    return 0;
}
