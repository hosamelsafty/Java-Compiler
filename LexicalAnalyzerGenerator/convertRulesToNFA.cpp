#include "convertRulesToNFA.h"
#include <fstream>
using namespace std;

void readRulesFile(const std::string &filename);

TransitionTable convertRulesToNFA(const std::string &filename)
{
	readRulesFile(filename);

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
