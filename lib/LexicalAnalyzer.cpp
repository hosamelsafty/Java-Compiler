#include "LexicalAnalyzer.h"
#include "ErrorLog.h"
#include <sstream>
#include <assert.h>

LexicalAnalyzer::LexicalAnalyzer(
    DFATransitionTable &transitionTable,
    std::istream& in,
    ErrorLog *errorLog,
    SymbolTable *symbolTable)
    : dfa_t(transitionTable), _streamWrapper(in), errorLog(errorLog), symbolTable(symbolTable)
{

}

LexicalAnalyzer::~LexicalAnalyzer()
{

}

Token* LexicalAnalyzer::nextToken()
{
    State currState = dfa_t.getStartingState();
    State nextState = currState;

    char c = EOF;
    State lastAcceptedState;
    bool accepted = false;
    std::string lexem, lastAcceptedLexem;
    std::string undefinedString;

    int startPos = _streamWrapper.getPos();

    // Loop getting single characters
    while ((c = _streamWrapper.getNext()) != EOF)
    {
        lexem += c;

        if (dfa_t.checkTransition(currState, c)) // a transition found.
        {
            nextState = dfa_t.nextState(currState, c);
            //indx++;

            if (dfa_t.isAcceptingState(nextState))
            {
                lastAcceptedState = nextState;
                lastAcceptedLexem = lexem;
                //lastAccIndx = indx;
                accepted = true;
            }
            currState = nextState;
        }
        else if (accepted) // no transition found while a previous accepted input is found
        {
            break;
        }
        else // no transition found and not accepted input found
        {
            // Error: Undefined input of /lexem/
            // Recover by removing the first char and start again
            undefinedString += lexem[0];
            _streamWrapper.putFront(lexem.substr(1, lexem.size() - 1));
            lexem = "";
            currState = dfa_t.getStartingState();
            nextState = currState;
        }
    }

    Token *token = nullptr;

    if (accepted)
    {
        // Token Type according to lastAcceptedState
        // position = startPos + undefinedString.size()
        token = new Token(lastAcceptedState.getTokenType(), lastAcceptedLexem);

        if (lexem.size() > lastAcceptedLexem.size())
            _streamWrapper.putFront(lexem.substr(lastAcceptedLexem.size(), lexem.size() - lastAcceptedLexem.size()));
    }
    else // No accepted input.
    {
        // Has to arrive at EOF
        assert(c == EOF);
        assert(lexem.empty());
    }

    if (undefinedString.size())
    {
        // Error: Undefined input of /undefinedString/
        // position = startPosition
    }

    return token;
}

