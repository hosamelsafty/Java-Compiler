#include "LexicalAnalyzer.h"

#include <sstream>
#include <assert.h>

#include "ErrorLog.h"
#include "StreamWrapper.h"
#include "DFATransitionTable.h"

struct LexicalAnalyzer::impl
{
    DFATransitionTable dfa;
    StreamWrapper _streamWrapper;
    ErrorLog * errorLog;
    SymbolTable * symbolTable;

    impl(const DFATransitionTable &dfa,
        std::istream& in,
        ErrorLog *errorLog,
        SymbolTable *symbolTable)
        : dfa(dfa), _streamWrapper(in), errorLog(errorLog), symbolTable(symbolTable)
    {
    }
};

LexicalAnalyzer::LexicalAnalyzer(
    const DFATransitionTable &dfa,
    std::istream& in,
    ErrorLog *errorLog,
    SymbolTable *symbolTable)
    : m_d(std::make_unique<impl>(dfa, in, errorLog, symbolTable))
{
}

LexicalAnalyzer::~LexicalAnalyzer()
{

}

Token* LexicalAnalyzer::nextToken()
{
    StateId currState = m_d->dfa.getStartingState();
    StateId nextState = currState;

    char c = EOF;
    StateId lastAcceptedState;
    bool accepted = false;
    std::string lexem, lastAcceptedLexem;
    std::string undefinedString;

    const int startPos = m_d->_streamWrapper.getPos();

    // Loop getting single characters
    while ((c = m_d->_streamWrapper.getNext()) != EOF)
    {
        lexem += c;

        if (m_d->dfa.hasTransition(currState, c)) // a transition found.
        {
            nextState = m_d->dfa.move(currState, c);

            if (m_d->dfa.isAcceptingState(nextState))
            {
                lastAcceptedState = nextState;
                lastAcceptedLexem = lexem;
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
            m_d->_streamWrapper.putFront(lexem.substr(1, lexem.size() - 1));
            lexem = "";
            currState = m_d->dfa.getStartingState();
            nextState = currState;
        }
    }

    Token *token = nullptr;

    if (accepted)
    {
        // Token Type according to lastAcceptedState
        // position = startPos + undefinedString.size()
        State acceptedState = m_d->dfa.getState(lastAcceptedState);
        token = new Token(acceptedState.getTokenType(), lastAcceptedLexem);

        if (lexem.size() > lastAcceptedLexem.size())
            m_d->_streamWrapper.putFront(lexem.substr(lastAcceptedLexem.size(), lexem.size() - lastAcceptedLexem.size()));
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
        m_d->errorLog->add(undefinedString, startPos, startPos, "Undefined input");
    }

    return token;
}

