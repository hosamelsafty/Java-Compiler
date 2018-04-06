#include "lib/ErrorLog.h"
#include "lib/NFATransitionTable.h"
#include "lib/LexicalAnalyzer.h"
#include "readTransitionTable.h"
#include "writeErrorLogToFile.h"
#include "printTokensToScreen.h"
#include <fstream>


int main(int argc, char** argv)
{
    // Skip the executable name
    argc--; argv++;

    if (argc == 0)
    {
        cout << "Please insert the path for a c code file on the command line. Example: LexicalAnalyzer prog.c";
        return 0;
    }

    std::string transitionTableFilename = "dfa.json";

    // Read TransitionTable from file
    // input: filename
    // output: TransitionTable
    DFATransitionTable dfa = readTransitionTable(transitionTableFilename);

    // Create ErrorLig
    ErrorLog errorLog;

    std::string codeFilename = argv[0];
    std::ifstream codeFile;

    // Create LexicalAnalyzer for the given code filename
    // input: TransitionTable, filename

    // TODO Check for return value
    codeFile.open(codeFilename);

    LexicalAnalyzer lexicalAnalyzer(dfa, codeFile, errorLog);


    // Execute the lexical analyzer to process the whole file
    // input: LexicalAnalyzer, ErrorLog
    // output: print tokens on screen
    printTokensToScreen(lexicalAnalyzer);

    // Write ErrorLog somewhere (in a file for example)
    // input: ErrorLog, filename
    // output: file containing error messages one per line.
    std::string errorLogFilename;
    writeErrorLogToFile(errorLog, errorLogFilename);

    return 0;
}
