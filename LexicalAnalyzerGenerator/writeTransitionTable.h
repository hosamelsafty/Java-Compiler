#ifndef writeTransitionTable_H
#define writeTransitionTable_H

#include <string>
#include "lib/DFATransitionTable.h"

void writeTransitionTable(const DFATransitionTable &dfa, const std::string &filename);

#endif // writeTransitionTable_H
