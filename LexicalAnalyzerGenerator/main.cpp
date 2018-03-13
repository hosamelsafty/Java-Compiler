
#include "minimizeDFA.h"
#include "convertNFAToDFA.h"
#include "convertRulesToNFA.h"
#include "writeTransitionTable.h"

#include "TransitionTable.h"

int main(int argc, char** argv)
{
    // TODO Read Rules file and convert to NFA
    // input: filename
    // output: TransitionTable
    TransitionTable nfa = convertRulesToNFA(filename);

    // TODO Convert NFA to DFA
    // input: TransitionTable
    // output: TransitionTable
    TransitionTable dfa = convertNFAToDFA(filename);

    // TODO minimize DFA
    // input: TransitionTable
    // output: TransitionTable
    TransitionTable minDFA= minimizeDFA(filename);

    // TODO write TransitionTable to file
    // input: TransitionTable, filename
    // file containing TransitionTable with proper format.
    writeTransitionTable(minDFA, filename);

    return 0;
}
