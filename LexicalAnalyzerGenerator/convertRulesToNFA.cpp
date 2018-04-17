#include "convertRulesToNFA.h"
#include <fstream>
#include "RulesHandler.h"
#include "lib/AcceptedTokenMap.h"

using namespace std;

NFATransitionTable constructPrimitiveNFA(string s);

NFATransitionTable convertRulesToNFA(const std::string &filename)
{
	RulesHandler rules(filename);
	rules.init_rules();
	int size = rules.regExp.size();
	vector<NFATransitionTable> nfas;
	for (int i = 1; i < size; ++i) {
		string postfix = rules.regExp[i].second;
		nfas.push_back(constructPrimitiveNFA(postfix));
        // Add mapping from end states of nfa to matched tokens
        AcceptedTokenMap::addNFAMapping(*nfas.back().getAcceptingStates().begin(),
                                        rules.regExp[i].first);
	}
	size = RulesHandler::keyword.size();
	for (int i = 0; i < size; ++i) {
		string postfix = rules.infixToPostfix(RulesHandler::keyword[i]);
		nfas.push_back(constructPrimitiveNFA(postfix));
		AcceptedTokenMap::addNFAMapping(*nfas.back().getAcceptingStates().begin(),
				RulesHandler::keyword[i]);
	}

	return NFATransitionTable::multiUnion(nfas);
}

bool  is_operator(char c){
	return c== '|' || c==' '||c== '+' || c=='*';
}

NFATransitionTable constructPrimitiveNFA(string s){

	stack<NFATransitionTable> stack;
	for (int i = 0; i < s.length(); ++i) {

		if(!is_operator(s[i])){
            if(s[i] == '\\'){
                i++;
				if(s[i] == 'L')
					s[i] = EPS;
			}
			NFATransitionTable nfa ;
			State start(State::newID());
			State end(State::newID());
            nfa.setStartingStates(set<State>{start});
			nfa.setAcceptingStates(set<State>{end});
			nfa.setTransition(start, s[i], end);
			stack.push(nfa);
		}
		else {
			if(s[i]=='|'){
				NFATransitionTable nfa2=stack.top();
				stack.pop();
				NFATransitionTable nfa1=stack.top();
				stack.pop();
				stack.push(nfa1.opUnion(nfa2));
			}

			else if(s[i]==' '){
				NFATransitionTable nfa2=stack.top();
				stack.pop();
				NFATransitionTable nfa1=stack.top();
				stack.pop();
				stack.push(nfa1.opConcat(nfa2));
			}
			else if(s[i]=='*'){
				NFATransitionTable nfa=stack.top();
				stack.pop();
				stack.push(nfa.opStar());
			}
			else if(s[i]=='+'){
				NFATransitionTable nfa=stack.top();
				stack.pop();
				stack.push(nfa.opPlus());
			}
		}
	}

	return stack.top();

}
