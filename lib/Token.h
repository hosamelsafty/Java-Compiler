#ifndef Token_H
#define Token_H

class Token {
public:
	Token(std::string l, std::string t) {
		lexem = l;
		token = t;
	}
	std::string lexem;
	std::string token;
	std::ostream& operator<<(std::ostream& out) {
		out << lexem;
		return out;
	}
};
#endif // Token_H
