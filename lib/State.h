#ifndef State_H
#define State_H
#include <iostream>
#include <string>

enum Type
{
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
	State(int);
    State(int,const std::string);
    State(int,const std::string,Type);
	std::string getMatchedToken() const;

	void setType(Type t);
	Type getType() const;
	int getID() const;
  	static int new_id;
	const State &operator=(const State &s);
	bool operator==(const State & s) const;
	static int newID()
	{
		return new_id++;
	}
};
bool operator<(const State &lhs, const State &rhs);

#endif // State_H
