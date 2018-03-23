#include "LexicalAnalyzer.h"
#include "ErrorLog.h"
#include <sstream>

LexicalAnalyzer::LexicalAnalyzer(
		DFATransitionTable &transitionTable, std::istream& in,
		ErrorLog &errorLog) :
		input(in), dfa_t(transitionTable) {
	remainingInput = "";
}

LexicalAnalyzer::LexicalAnalyzer(
		DFATransitionTable &transitionTable, std::istream& in) :
		input(in), dfa_t(transitionTable) {
	remainingInput = "";
}

LexicalAnalyzer::~LexicalAnalyzer() {

}

Token* LexicalAnalyzer::getToken(std::istream& io) {
	std::string lexem = "";
	int indx = 0, lastAccIndx;
	char c;
	State currState = dfa_t.getStartingState();
	State* lastAcceptedState = NULL;
	State nextState;
	while (io.peek() != EOF && io.get(c)) { // loop getting single characters
		if (dfa_t.checkTransition(currState, c)) { // a transition found.
			nextState = dfa_t.nextState(currState, c);
			indx++;
			lexem += c;
			for (auto& i : dfa_t.getAcceptingStates()) {
				if (nextState == i) {
					lastAcceptedState = &nextState;
					lastAccIndx = indx;
					break;
				}
			}
			currState = nextState;
		} else { // no transition found.
			break;
		}
	}
	if (!lexem.size())
		return NULL;
	if (!lastAcceptedState) {
		return NULL;
	}
	remainingInput = lexem.substr(lastAccIndx,
			lexem.size() - lastAccIndx);
	Token* t = new Token("Token1", lexem.substr(0, lastAccIndx));
	return t;
}
Token* LexicalAnalyzer::nextToken() {
	Token* token;
	if (!remainingInput.empty()) {
		std::istringstream ss;
		ss.str(remainingInput);
		token = getToken(ss);
	} else {
		token = getToken(input);
	}
	return token;
}
