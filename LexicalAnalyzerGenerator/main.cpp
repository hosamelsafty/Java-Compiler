#include "minimizeDFA.h"
#include "TransitionTable.h"
#include "convertNFAToDFA.h"
#include "convertRulesToNFA.h"
#include "writeTransitionTable.h"

#include <string>

int main(int argc, char** argv)
{
	std::string filename;

    // TODO Read Rules file and convert to NFA
    // input: filename
    // output: TransitionTable
    TransitionTable nfa = convertRulesToNFA(filename);

    // TODO Convert NFA to DFA
    // input: TransitionTable
    // output: TransitionTable
    TransitionTable dfa = convertNFAToDFA(nfa);

    // TODO minimize DFA
    // input: TransitionTable
    // output: TransitionTable
    TransitionTable minDFA= minimizeDFA(dfa);

    // TODO write TransitionTable to file
    // input: TransitionTable, filename
    // file containing TransitionTable with proper format.
    writeTransitionTable(minDFA, filename);

    return 0;
}
