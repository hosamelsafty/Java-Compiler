#ifndef convertNFAToDFA_H
#define convertNFAToDFA_H

#include "lib/NFATransitionTable.h"
#include "lib/DFATransitionTable.h"

DFATransitionTable convertNFAToDFA(const NFATransitionTable &nfa);

#endif // convertNFAToDFA_H
