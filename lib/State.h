#ifndef State_H
#define State_H

#include <string>

class State
{
public:
	State();
	State(const std::string name);

	std::string name;
};

bool operator<(const State &lhs, const State &rhs);

#endif // State_H
