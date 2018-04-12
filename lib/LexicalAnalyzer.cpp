#include "LexicalAnalyzer.h"
#include "ErrorLog.h"
#include "LexicalAnalyzerGenerator/RulesHandler.h"
#include <sstream>
#include <algorithm>

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
		if (c == '\n' && lexem.size() == 0) {
			noLine++;
			continue;
		} else if (c == '\n') {
			indx++;
			lexem += c;
			return;
		}
		if (c == ' ' && lexem.size() == 0) {
			continue;
		} else if (c == ' ') {
			indx++;
			lexem += c;
			return;
		}
		for (string s : RulesHandler::punc) {
			if (s[0] == c) {
				indx++;
				lexem += c;
				return;
			}
		}
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
	if (remainingInput.size() == 0  && input.peek() == EOF) {
		return NULL;
	}
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
	getToken(input, lexem, indx, lastAccIndx, currState,
			lastAcceptedState);
	if (!lexem.size()) // end of input
		return new Token("", "");
	if (lexem.size() == 1) {
		for (string s : RulesHandler::punc) {	// punctuation.
			if (lexem[0] == s[0]) {
				Token* t = new Token(lexem, lexem);
				return t;
			}
		}
	}
	if (lastAcceptedState.getID() == -1) { // end of input and an Error.
		errLog.add(lexem, noLine, "No matched Token");
		return new Token("", "");
	}
	remainingInput = lexem.substr(lastAccIndx,
			lexem.size() - lastAccIndx);
	string value = lexem.substr(0, lastAccIndx);
	string type = AcceptedTokenMap::getDFAMapping(
			lastAcceptedState);
	for (auto& key : RulesHandler::keyword) {
		if (key == value) {
			type = key;
			break;
		}
	}
	Token* t = new Token(type, value);
	return t;
}
