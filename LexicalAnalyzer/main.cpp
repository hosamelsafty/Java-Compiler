#include "ErrorLog.h"
#include "TransitionTable.h"
#include "LexicalAnalyzer.h"
#include "readTransitionTable.h"
#include "writeErrorLogToFile.h"
#include "printTokensToScreen.h"

int main(int argc, char** argv)
{
    // TODO Read TransitionTable from file
    // input: filename
    // output: TransitionTable
    TransitionTable dfa = readTransitionTable(transitionTableFilename);

    // TODO Create ErrorLig 
    ErrorLog errorLog;

    // TODO Create LexicalAnalyzer for the given code filename
    // input: TransitionTable, filename
    LexicalAnalyzer lexicalAnalyzer(dfa, codeFilename, errorLog);

    // TODO execute the lexical analyzer to process the whole file
    // input: LexicalAnalyzer, ErrorLog
    // output: print tokens on screen
    printTokensToScreen(LexicalAnalyzer);

    // TODO write ErrorLog somewhere (in a file for example)
    // input: ErrorLog, filename
    // output: file containing error messages one per line.
    writeErrorLogToFile(errorLog, errorLogFilename);

    return 0;
}
