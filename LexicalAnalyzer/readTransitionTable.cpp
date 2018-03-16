#include "readTransitionTable.h"

#include <fstream>

TransitionTable readTransitionTable(const std::string &filename)
{
	TransitionTable transitionTable;
	std::ifstream file;
	file.open(filename);
	file >> transitionTable;
	file.close();
	return transitionTable;
}
