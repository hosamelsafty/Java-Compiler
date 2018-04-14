#ifndef convertRulesToNFA_H
#define convertRulesToNFA_H

#include <string>
#include "lib/NFATransitionTable.h"

NFATransitionTable convertRulesToNFA(const std::string &filename);

#endif // convertRulesToNFA_H