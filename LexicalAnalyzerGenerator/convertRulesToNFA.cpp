#include "convertRulesToNFA.h"
#include <fstream>
#include "RulesHandler.h"
using namespace std;

void readRulesFile(const std::string &filename);

NFATransitionTable convertRulesToNFA(const std::string &filename)
{
<<<<<<< HEAD

	RulesHandler rules;

	rules.init_rules();
	return TransitionTable();
=======
	return NFATransitionTable();
>>>>>>> 6ba43079a8ba85c427d76e42eb900c70cd03d05e
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
