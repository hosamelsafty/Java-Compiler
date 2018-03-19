#include "LexicalAnalyzer.h"
#include "ErrorLog.h"

LexicalAnalyzer::LexicalAnalyzer(
		const DFATransitionTable &transitionTable,
		std::istream& in, ErrorLog &errorLog) :
		input(in), errLog(errorLog), dfa_t(transitionTable) {
	remainingInput = "";
}

LexicalAnalyzer::~LexicalAnalyzer() {

}
Token LexicalAnalyzer::nextToken() {
	std::string lexem = "";
	int indx = 0, lastAccIndx;
	char c;
	State currState = dfa_t.getStartingState(),
			lastAcceptedState;
	while (remainingInput.size()) {
		c = *remainingInput.erase(0, 1);
		State nextState = dfa_t.nextState(currState, c);
		if (nextState) { // a transition found.
			indx++;
			lexem += c;
			if (nextState.getType() == ACCEPTING) {
				lastAcceptedState = nextState;
				lastAccIndx = indx;
			}
			currState = nextState;
		} else { // no transition found.
			remainingInput
					== lexem.substr(lastAccIndx,
							lexem.size() - lastAccIndx);
			return Token(lexem.substr(0, lastAccIndx),
					lastAcceptedState.getMatchedToken());
		}
	}
	while (input.get(c)) {	 // loop getting single characters
		State nextState = dfa_t.nextState(currState, c);
		if (nextState) { // a transition found.
			indx++;
			lexem += c;
			if (nextState.getType() == ACCEPTING) {
				lastAcceptedState = nextState;
				lastAccIndx = indx;
			}
			currState = nextState;
		} else { // no transition found.
			break;
		}
	}
	remainingInput = lexem.substr(lastAccIndx,
			lexem.size() - lastAccIndx);
	return Token(lexem.substr(0, lastAccIndx),
			lastAcceptedState.getMatchedToken());
}
