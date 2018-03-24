#ifndef convertRulesToNFA_H
#define convertRulesToNFA_H

#include <string>
#include "lib/NFATransitionTable.h"

NFATransitionTable convertRulesToNFA(const std::string &filename);
NFATransitionTable constructPrimitiveNFA(const std::string s);

#endif // convertRulesToNFA_H