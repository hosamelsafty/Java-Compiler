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
};

#endif // Token_H
