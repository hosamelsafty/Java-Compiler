#include "minimizeDFA.h"
#include "TransitionTable.h"
#include "convertNFAToDFA.h"
#include "convertRulesToNFA.h"
#include "writeTransitionTable.h"

#include <string>

int main(int argc, char** argv)
{
	std::string rulesFilename;

    // TODO Read Rules file and convert to NFA
    // input: filename
    // output: TransitionTable
    TransitionTable nfa = convertRulesToNFA(rulesFilename);

    // TODO Convert NFA to DFA
    // input: TransitionTable
    // output: TransitionTable
    TransitionTable dfa = convertNFAToDFA(nfa);

    // TODO minimize DFA
    // input: TransitionTable
    // output: TransitionTable
    TransitionTable minDFA= minimizeDFA(dfa);

	// Examples
	minDFA.add(std::set<State>{State("asd"), State("qwe")}, 'a', std::set<State>{State("asd"), State("qwe")});
	minDFA.add(std::set<State>{State("asd"), State("qwe")}, 'b', std::set<State>{State("asd"), State("qwe")});

    // TODO write TransitionTable to file
    // input: TransitionTable, filename
    // file containing TransitionTable with proper format.
	std::string outputFilename = "tt.json";
    writeTransitionTable(minDFA, outputFilename);

    return 0;
}
