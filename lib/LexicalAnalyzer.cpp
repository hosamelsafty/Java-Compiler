#include "LexicalAnalyzer.h"
#include "ErrorLog.h"
#include <sstream>

LexicalAnalyzer::LexicalAnalyzer(
		DFATransitionTable &transitionTable, std::istream& in,
		ErrorLog &errorLog) :
		input(in), dfa_t(transitionTable), errLog(errorLog) {
	remainingInput = "";
	noLine = 1;
}

LexicalAnalyzer::~LexicalAnalyzer() {

}

void LexicalAnalyzer::getToken(std::istream& io,
		std::string &lexem, int &indx, int &lastAccIndx,
		State& currState, State& lastAcceptedState) {
	char c;
	State nextState;
	while (io.peek() != EOF && io.get(c)) { // loop getting single characters
//		if (c is in Punctuations and not an '\n')
//			add it to lexem and return.
//			if it \n then  noLine++;
		if (dfa_t.checkTransition(currState, c)) { // a transition found.
			nextState = dfa_t.nextState(currState, c);
			indx++;
			lexem += c;
			if (dfa_t.isAcceptingState(nextState)) {
				lastAcceptedState = nextState;
				lastAccIndx = indx;
			}
			currState = nextState;
		} else { // no transition found.
			break;
		}
	}
}
Token* LexicalAnalyzer::nextToken() {
	std::string lexem = "";
	int indx = 0, lastAccIndx;
	State currState = dfa_t.getStartingState();
	State lastAcceptedState(-1);	// not valid state.
	if (!remainingInput.empty()) { // process the remaining input first.
		std::istringstream ss;
		ss.str(remainingInput);
		getToken(ss, lexem, indx, lastAccIndx, currState,
				lastAcceptedState);
		ss.clear();
	}
//	if (lexem.size() == 1 && lexem[0] is in Punctuations)
//	Token* t = new Token ("Punctuation",lexem);
	getToken(input, lexem, indx, lastAccIndx, currState,
			lastAcceptedState);
	if (!lexem.size()) // end of input
		return NULL;
	if (lastAcceptedState.getID() == -1) { // end of input and an Error.
		errLog.add(lexem, noLine, "No matched Token");
		return NULL;
	}
	remainingInput = lexem.substr(lastAccIndx,
			lexem.size() - lastAccIndx);
	Token* t = new Token("Token1", lexem.substr(0, lastAccIndx));

	return t;
}
