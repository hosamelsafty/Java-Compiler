#include "convertRulesToNFA.h"
#include <fstream>
#include "RulesHandler.h"
using namespace std;

void readRulesFile(const std::string &filename);

TransitionTable convertRulesToNFA(const std::string &filename)
{

	RulesHandler rules;

	rules.init_rules();
	return TransitionTable();
}

void readRulesFile(const std::string &filename){
	string line;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
	  while ( getline (myfile,line) )
	  {
	    cout << line << '\n';
	  }
	  myfile.close();
	}

	else cout << "Unable to open file";
}
