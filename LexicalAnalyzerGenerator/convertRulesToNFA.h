#ifndef convertRulesToNFA_H
#define convertRulesToNFA_H

#include <string>
#include "lib/NFATransitionTable.h"

NFATransitionTable convertRulesToNFA(const std::string &filename);
NFATransitionTable constructPrimitiveNFA(const std::string s);
NFATransitionTable Union(NFATransitionTable nfa1,NFATransitionTable nfa2);
NFATransitionTable Concat(NFATransitionTable nfa1,NFATransitionTable nfa2);
NFATransitionTable Star(NFATransitionTable nfa);
NFATransitionTable Plus(NFATransitionTable nfa);
NFATransitionTable MultiUnion(NFATransitionTable nfas[] );
#endif // convertRulesToNFA_H