#ifndef convertRulesToNFA_H
#define convertRulesToNFA_H

#include <string>
#include "lib/NFATransitionTable.h"

NFATransitionTable convertRulesToNFA(const std::string &filename);
NFATransitionTable constructPrimitiveNFA(const std::string s);
NFATransitionTable MultiUnion(std::vector<std::pair <NFATransitionTable ,std::string >> nfas);

#endif // convertRulesToNFA_H
