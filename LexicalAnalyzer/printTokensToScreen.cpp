#include "printTokensToScreen.h"

vector<Token> symbol_table;
void add_in_symbol_table(Token* t);
void printTokensToScreen(LexicalAnalyzer &lexicalAnalyzer) {
	Token* token = lexicalAnalyzer.nextToken();
	while (token) {
		if (token->type.size()) {
			cout << token->type << endl;
//			add_in_symbol_table (Token);
		}
//		cout << "Calling" << endl;
		token = lexicalAnalyzer.nextToken();
	}
}
void add_in_symbol_table(Token* t) {
	symbol_table.push_back(*t);
}
