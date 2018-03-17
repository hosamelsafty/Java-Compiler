#ifndef State_H
#define State_H

enum Type{
	REGULAR,
	STARTING,
	ACCEPTING,
};

class State
{
	int id;
	Type type;
public:
	State(int number);
	void setType(Type t);
	Type getType() const;
	int getID() const;
};

bool operator<(const State &lhs, const State &rhs);

#endif // State_H
