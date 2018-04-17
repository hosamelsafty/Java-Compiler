//#include "lib/ErrorLog.h"
//#include "lib/NFATransitionTable.h"
//#include "lib/LexicalAnalyzer.h"
//#include "lib/AcceptedTokenMap.h"
//#include "LexicalAnalyzerGenerator/minimizeDFA.h"
//#include "readTransitionTable.h"
//#include "writeErrorLogToFile.h"
//#include "printTokensToScreen.h"
//#include <fstream>
//#include <sstream>
//
//int main(int argc, char** argv) {
//	std::string transitionTableFilename;
//
//	// input: filename
//	// output: TransitionTable
////	DFATransitionTable dfa= readTransitionTable(transitionTableFilename);
//	State s0 = State(0);
//	s0.setType(STARTING);
//	State s1 = State(1);
//	s1.setType(ACCEPTING);
//	AcceptedTokenMap::addDFAMapping(s1,"hamada");
//	State s2 = State(2);
//	State s3 = State(3);
//	State s4 = State(4);
//	DFATransitionTable dfa;
//	dfa.setStartingState(s0);
//	dfa.addAcceptingState(s1);
//	dfa.add(s0, '0', s1);
//	dfa.add(s0, '1', s2);
//	dfa.add(s1, '0', s2);
//	dfa.add(s1, '1', s3);
//	dfa.add(s2, '0', s1);
//	dfa.add(s2, '1', s2);
//	dfa.add(s3, '0', s0);
//	dfa.add(s3, '1', s2);
//	dfa.add(s4, '0', s3);
//	dfa.add(s4, '1', s4);
//	DFATransitionTable mini = minimizeDFA(dfa);
//	// TODO Create ErrorLig
//	ErrorLog errorLog;
//
//	istringstream codeFile;
//	string string1 = "01110010011010111";
//	codeFile.str(string1);
//	//	ss.clear();
//	// TODO Create LexicalAnalyzer for the given code filename
//	// input: TransitionTable, filename
////	std::string codeFilename;
////	std::ifstream codeFile;
////	// TODO Check for return value
////	codeFile.open(codeFilename);
//
//	LexicalAnalyzer lexicalAnalyzer(dfa, codeFile, errorLog);
//
//	// TODO execute the lexical analyzer to process the whole file
//	// input: LexicalAnalyzer, ErrorLog
//	// output: print tokens on screen
//	printTokensToScreen(lexicalAnalyzer);
//
//	// TODO write ErrorLog somewhere (in a file for example)
//	// input: ErrorLog, filename
//	// output: file containing error messages one per line.
//	std::string errorLogFilename = "errorLog.txt";
//	writeErrorLogToFile(errorLog, errorLogFilename);
//
//	return 0;
//}
