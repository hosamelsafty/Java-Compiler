#ifndef State_H
#define State_H

enum Type{
	REGULAR,
	STARTING,
	ACCEPTING,
};

class State
{
private:
	std::string matchToken; // every state should have the corresponding matched token.
	int id;
	Type type;
public:
	State();
    State(int,const std::string);
    std::string getMatchedToken() const;
	void setType(Type t);
	Type getType() const;
	int getID() const;
};

bool operator<(const State &lhs, const State &rhs);

#endif // State_H
