#include "LexicalAnalyzer.h"
#include "ErrorLog.h"
#include <sstream>

LexicalAnalyzer::LexicalAnalyzer(
		DFATransitionTable &transitionTable, std::istream& in, ErrorLog &errorLog) :
		input(in), dfa_t(transitionTable) {
	remainingInput = "";
}
LexicalAnalyzer::~LexicalAnalyzer() {

}

Token* LexicalAnalyzer::getToken(std::istream& io) {
	std::string lexem = "";
	int indx = 0, lastAccIndx;
	char c;
	State currState = dfa_t.startingState;
	State* lastAcceptedState = NULL;
	while (io.peek() != EOF && io.get(c)) { // loop getting single characters
		State* nextState = dfa_t.tryNextState(currState, c);
		if (nextState) { // a transition found.
			indx++;
			lexem += c;
			std::cout << lexem << std::endl;
			if (nextState->getType() == ACCEPTING) {
				lastAcceptedState = nextState;
				lastAccIndx = indx;
			}
			currState = *nextState;
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
	if(remainingInput.empty()){
		std::istringstream ss;
		ss.str(remainingInput);
		token = getToken(ss);
	}else{
		token = getToken(input);
	}
	return token;
}
