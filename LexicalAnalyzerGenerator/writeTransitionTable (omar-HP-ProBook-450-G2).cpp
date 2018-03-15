#include "writeTransitionTable.h"
#include <fstream>

void writeTransitionTable(const TransitionTable &dfa, const std::string &filename)
{
	std::ofstream file;
	file.open(filename);
	file << dfa;
	file.flush();
	file.close();
}
