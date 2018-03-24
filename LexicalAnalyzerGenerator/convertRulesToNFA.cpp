#include "convertRulesToNFA.h"
#include <fstream>
#include "RulesHandler.h"

using namespace std;



NFATransitionTable convertRulesToNFA(const std::string &filename)
{
	RulesHandler rules(filename);
	rules.init_rules();
	int size = rules.regExp.size()+rules.keyword.size();
	vector<std::pair <NFATransitionTable ,std::string >> nfas;
	for (int i = 0; i < size; ++i) {
		string postfix = rules.regExp[i].second;
		nfas.push_back(make_pair(constructPrimitiveNFA(postfix),rules.regExp[i].second));
	}
	for (int i = 0; i < size; ++i) {
		string postfix = rules.infixToPostfix(rules.keyword[i]);
		nfas.push_back(make_pair(constructPrimitiveNFA(postfix),rules.keyword[i]));
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
			start.setType(STARTING);
			State end(State::newID());
			end.setType(ACCEPTING);
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

NFATransitionTable MultiUnion(vector<pair<NFATransitionTable ,string > > nfas){
    /*NFATransitionTable newNFA;
    State startState(State::newID());
    newNFA.setStartingStates(set<State>{startState});

    int size = nfas.size();
    for (int i = 0; i < size; ++i) {
        newNFA.getAllTransitions().insert(newNFA.getAllTransitions().end(),
                                          nfas[i].getAllTransitions().begin(),nfas[i].getAllTransitions().end());
    }
    for (int j = 0; j < size; ++j) {
        for(auto& elem:nfas[j].getStartingStates()){
            newNFA.setTransition(startState,'\0', elem);
        }
    }
    */
    while(nfas.size() >=2){
        NFATransitionTable nfa1 = nfas.front().first;
        nfas.pop_back();
        NFATransitionTable nfa2 = nfas.front().first;
        nfas.pop_back();
        nfas.push_back(nfa1.opUnion(nfa2));
    }
    return nfas.front();
}
