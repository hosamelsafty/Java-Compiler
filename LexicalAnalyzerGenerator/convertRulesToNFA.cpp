#include "convertRulesToNFA.h"
#include <fstream>
#include "RulesHandler.h"

using namespace std;

// TODO hashmap
// TODO test pointer in operation

NFATransitionTable convertRulesToNFA(const std::string &filename)
{
	RulesHandler rules(filename);
	rules.init_rules();
	int size = rules.regExp.size();
	vector<NFATransitionTable> nfas;
	for (int i = 0; i < size; ++i) {
		string postfix = rules.regExp[i].second;
		nfas.push_back(constructPrimitiveNFA(postfix));
	}
	return MultiUnion(nfas);
}

bool  is_operator(char c){
	return c== '|' || c==' '||c== '+' || c=='*';
}

NFATransitionTable constructPrimitiveNFA(string s){

	stack<NFATransitionTable> stack;
	for (int i = 0; i < s.length(); ++i) {

		if(!is_operator(s[i])){
            if(s[i] == '\\')
                i++;
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
				NFATransitionTable nfa1=stack.top();
				stack.pop();
				NFATransitionTable nfa2=stack.top();
				stack.pop();
				stack.push(nfa1.opUnion(nfa2));
			}
			else if(s[i]==' '){
				NFATransitionTable nfa1=stack.top();
				stack.pop();
				NFATransitionTable nfa2=stack.top();
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

NFATransitionTable MultiUnion(vector<NFATransitionTable> nfas){
    while(nfas.size() >=2){
        NFATransitionTable nfa1 = nfas.back();
        nfas.pop_back();
        NFATransitionTable nfa2 = nfas.back();
        nfas.pop_back();
        nfas.push_back(nfa1.opUnion(nfa2));
    }
    return nfas.back();
}