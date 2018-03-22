#include "convertRulesToNFA.h"
#include <fstream>
#include "RulesHandler.h"

using namespace std;

// TODO hashmap
// TODO test pointer in operation

NFATransitionTable convertRulesToNFA(const std::string &filename)
{
	RulesHandler rules;
	rules.init_rules();
	int size = rules.regExp.size();
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
			NFATransitionTable nfa ;
			State start(State::newID());
			start.setType(STARTING);
			State end(State::newID());
			end.setType(ACCEPTING);
			nfa.startingSet = set<State>{start};
			nfa.endingSet = set<State>{end};
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
	NFATransitionTable newNfa ;
	State start(State::newID());
	start.setType(STARTING);
	State end(State::newID());
	end.setType(ACCEPTING);
	newNfa.startingSet = set<State>{start};
	newNfa.endingSet = set<State>{end};

	newNfa.add(newNfa.startingSet, '\0', nfa1.startingSet);
	newNfa.add(newNfa.startingSet, '\0', nfa2.startingSet);
	newNfa.add(nfa1.endingSet, '\0', newNfa.endingSet);
	newNfa.add(nfa2.endingSet, '\0', newNfa.endingSet);
	return newNfa;
}


NFATransitionTable Concat(NFATransitionTable nfa1,NFATransitionTable nfa2){
	NFATransitionTable newNfa;

	newNfa.startingSet=nfa1.startingSet;
	nfa1.endingSet=nfa2.startingSet;
	newNfa.endingSet=nfa2.endingSet;

	return newNfa;
}


NFATransitionTable Star(NFATransitionTable nfa){
	NFATransitionTable newNfa ;
	State start(State::newID());
	start.setType(STARTING);
	State end(State::newID());
	end.setType(ACCEPTING);
	newNfa.startingSet = set<State>{start};
	newNfa.endingSet = set<State>{end};

	newNfa.add(newNfa.startingSet, '\0', nfa.startingSet);
	newNfa.add(newNfa.startingSet, '\0', newNfa.endingSet);
	newNfa.add(nfa.endingSet, '\0', nfa.startingSet);
	newNfa.add(nfa.endingSet, '\0', newNfa.endingSet);
	return newNfa;
}


NFATransitionTable Plus(NFATransitionTable nfa){
	NFATransitionTable newNfa ;
	State start(State::newID());
	start.setType(STARTING);
	State end(State::newID());
	end.setType(ACCEPTING);
	newNfa.startingSet = set<State>{start};
	newNfa.endingSet = set<State>{end};

	NFATransitionTable tempNFA=nfa;
	newNfa.add(newNfa.startingSet, '\0', nfa.startingSet);
	newNfa.add(newNfa.startingSet, '\0', newNfa.endingSet);
	newNfa.add(nfa.endingSet, '\0', nfa.startingSet);
	newNfa.add(nfa.endingSet, '\0', newNfa.endingSet);
}

NFATransitionTable MultiUnion(NFATransitionTable nfas[]){


}