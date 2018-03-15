#include "lib/ErrorLog.h"
#include "lib/TransitionTable.h"
#include "lib/LexicalAnalyzer.h"
#include "readTransitionTable.h"
#include "writeErrorLogToFile.h"
#include "printTokensToScreen.h"
#include <fstream>


int main(int argc, char** argv)
{
	std::string transitionTableFilename;

    // TODO Read TransitionTable from file
    // input: filename
    // output: TransitionTable
    TransitionTable dfa = readTransitionTable(transitionTableFilename);

    // TODO Create ErrorLig
    ErrorLog errorLog;

	std::string codeFilename;
	std::ifstream codeFile;

    // TODO Create LexicalAnalyzer for the given code filename
    // input: TransitionTable, filename

	// TODO Check for return value
	codeFile.open(codeFilename);

    LexicalAnalyzer lexicalAnalyzer(dfa, codeFile, errorLog);


    // TODO execute the lexical analyzer to process the whole file
    // input: LexicalAnalyzer, ErrorLog
    // output: print tokens on screen
    printTokensToScreen(lexicalAnalyzer);

    // TODO write ErrorLog somewhere (in a file for example)
    // input: ErrorLog, filename
    // output: file containing error messages one per line.
	std::string errorLogFilename;
    writeErrorLogToFile(errorLog, errorLogFilename);

    return 0;
}
