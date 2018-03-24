#include "minimizeDFA.h"
#include "convertNFAToDFA.h"
#include "convertRulesToNFA.h"
#include "writeTransitionTable.h"

#include "lib/NFATransitionTable.h"

#include <string>

int main(int argc, char** argv)
{
    using namespace std;
    // This is Tested ##
    NFATransitionTable nfa = convertRulesToNFA("C:/Users/win8.1/Desktop/compiler/javacompiler/domx.txt");
    DFATransitionTable dfa1 = convertNFAToDFA(nfa);

    for (State s:dfa1.getStates()) {
        cout << "StateID:" << s.getID() << " , type:" << s.getType() << endl;
        for(auto& pair: dfa1.getMapping(s)){
            cout << "Under char '" << pair.first<< "' , it goes to stateID:" << pair.second.getID()<<endl;
        }
    }

    cout << "-------------------------------------------" << endl;

    return 0;
}
