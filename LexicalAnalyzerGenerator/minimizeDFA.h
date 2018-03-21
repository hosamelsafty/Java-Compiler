#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef minimizeDFA_H
#define minimizeDFA_H

#include "lib/DFATransitionTable.h"

DFATransitionTable minimizeDFA(const DFATransitionTable &dfa);

#endif // minimizeDFA_H