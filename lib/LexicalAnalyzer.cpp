#include "LexicalAnalyzer.h"
#include "ErrorLog.h"

LexicalAnalyzer::LexicalAnalyzer(
		DFATransitionTable &transitionTable, std::istream& in) :
		input(in), dfa_t(transitionTable) {
	remainingInput = "";
}
LexicalAnalyzer::~LexicalAnalyzer() {

}
Token* LexicalAnalyzer::nextToken() {
	std::string lexem = "";
	int indx = 0, lastAccIndx;
	char c;
	State currState = State(dfa_t.getStartingState().getID(),
			dfa_t.getStartingState().getMatchedToken(),
			dfa_t.getStartingState().getType());
	State* lastAcceptedState = NULL;
	while (!remainingInput.empty()) {
		c = remainingInput[0];
		remainingInput.erase(0, 1);
		std::cout << "reamdf : " << remainingInput.empty()
				<< std::endl;
		State* nextState = dfa_t.nextState(currState, c);
		if (nextState) { // a transition found.
			indx++;
			lexem += c;
			if (nextState->getType() == ACCEPTING) {
				lastAcceptedState = nextState;
				lastAccIndx = indx;
			}
			currState = State(nextState->getID(),
					nextState->getMatchedToken(),
					nextState->getType());
		} else { // no transition found.
			if (!lexem.size())
				return NULL;
			remainingInput
					== lexem.substr(lastAccIndx,
							lexem.size() - lastAccIndx);
			Token* t = new Token(lexem.substr(0, lastAccIndx),
					lastAcceptedState->getMatchedToken());
			return t;
		}
	}
	while (input.peek() != EOF && input.get(c)) { // loop getting single characters
		State* nextState = dfa_t.nextState(currState, c);
		if (nextState) { // a transition found.
			indx++;
			lexem += c;
			std::cout << lexem << std::endl;
			if (nextState->getType() == ACCEPTING) {
				lastAcceptedState = nextState;
				lastAccIndx = indx;
			}
			currState = State(nextState->getID(),
					nextState->getMatchedToken(),
					nextState->getType());
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
	Token* t = new Token(lexem.substr(0, lastAccIndx),
			lastAcceptedState->getMatchedToken());
	return t;
}
