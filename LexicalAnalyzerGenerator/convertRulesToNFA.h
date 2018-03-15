#ifndef convertRulesToNFA_H
#define convertRulesToNFA_H

#include <string>
#include "lib/TransitionTable.h"

TransitionTable convertRulesToNFA(const std::string &filename);

#endif // convertRulesToNFA_H
