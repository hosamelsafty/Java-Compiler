#include "convertRulesToNFA.h"
#include <fstream>
#include "RulesHandler.h"
#include "NFATransitionTable.h"
using namespace std;

// TODO hashmap
// TODO test pointer in operation

NFATransitionTable convertRulesToNFA(const std::string &filename)
{

	RulesHandler rules;

	rules.init_rules();
	int size=rules.regExp.size();
	NFATransitionTable nfas[size];
	for (int i = 0; i < size; ++i) {
		string postfix = rules.regExp[i].second;
		nfas[i] = constructPrimitiveNFA(postfix);
//		cout<<nfas[i].startingSet<<endl;
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
			State state;
			NFATransitionTable nfa ;
				nfa.startingSet=set<State>{
					State(State::newID()).setType(STARTING)
				};
				nfa.endingSet=set<State>{
						State(State::newID()).setType(ACCEPTING)
					};
				nfa.add(nfa.startingSet, s[i], nfa.endingSet);
				stack.push(nfa);
		}
		else {
			if(s[i]=='|'){
				NFATransitionTable nfa1=stack.top();
				stack.pop();
				NFATransitionTable nfa2=stack.top();
				stack.pop();
				stack.push(Union(nfa1,nfa2));
			}
			else if(s[i]==' '){
				NFATransitionTable nfa1=stack.top();
				stack.pop();
				NFATransitionTable nfa2=stack.top();
				stack.pop();
				stack.push(Concat(nfa1, nfa2));
			}
			else if(s[i]=='*'){
				NFATransitionTable nfa=stack.top();
				stack.pop();
				stack.push(Star(nfa));
			}
			else if(s[i]=='+'){
				NFATransitionTable nfa=stack.top();
				stack.pop();
				stack.push(Plus(nfa));
			}


		}
	}

	return NFATransitionTable();

}
NFATransitionTable Union(NFATransitionTable nfa1,NFATransitionTable nfa2){
	NFATransitionTable nfa;
	nfa.startingSet=set<State>{
	State(State::newID()).setType(STARTING)
	};
	nfa.endingSet=set<State>{
	State(State::newID()).setType(ACCEPTING)
	};
	nfa.add(nfa.startingSet, '\L', nfa1.startingSet);
	nfa.add(nfa.startingSet, '\L', nfa2.startingSet);
	nfa.add(nfa1.endingSet, '\L', nfa.endingSet);
	nfa.add(nfa2.endingSet, '\L', nfa.endingSet);
	return nfa;
}


NFATransitionTable Concat(NFATransitionTable nfa1,NFATransitionTable nfa2){
	NFATransitionTable nfa;

	nfa.startingSet=nfa1.startingSet;
	nfa1.endingSet=nfa2.startingSet;
	nfa.endingSet=nfa2.endingSet;

return nfa;
}


NFATransitionTable Star(NFATransitionTable nfa){
	NFATransitionTable newNFA;
	newNFA.startingSet=set<State>{
	State(State::newID()).setType(STARTING)
	};
	newNFA.endingSet=set<State>{
	State(State::newID()).setType(ACCEPTING)
	};
	newNFA.add(newNFA.startingSet, '\L', nfa.startingSet);
	newNFA.add(newNFA.startingSet, '\L', newNFA.endingSet);
	newNFA.add(nfa.endingSet, '\L', nfa.startingSet);
	newNFA.add(nfa.endingSet, '\L', newNFA.endingSet);
	return newNFA;
}


NFATransitionTable Plus(NFATransitionTable nfa){
	NFATransitionTable newNFA;
	newNFA.startingSet=set<State>{
	State(State::newID()).setType(STARTING)
	};
	newNFA.endingSet=set<State>{
	State(State::newID()).setType(ACCEPTING)
	};
	NFATransitionTable tempNFA=nfa;
	newNFA.add(newNFA.startingSet, '\L', nfa.startingSet);
		newNFA.add(newNFA.startingSet, '\L', newNFA.endingSet);
		newNFA.add(nfa.endingSet, '\L', nfa.startingSet);
		newNFA.add(nfa.endingSet, '\L', newNFA.endingSet);
}
NFATransitionTable MultiUnion(NFATransitionTable nfas[]){


}
