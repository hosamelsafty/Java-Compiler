#include "printTokensToScreen.h"

void printTokensToScreen(LexicalAnalyzer &lexicalAnalyzer)
{
	Token* token = lexicalAnalyzer.nextToken();
	while (token){
		cout << token->type << endl;
		token = lexicalAnalyzer.nextToken();
	}
}
