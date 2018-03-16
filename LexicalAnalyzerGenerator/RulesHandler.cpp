/*
 * RulesHandler.cpp
 *
 *  Created on: Mar 14, 2018
 *      Author: hosamelsafty
 */


#include "RulesHandler.h"
#include <fstream>
#include <iostream>
using namespace std;

RulesHandler::RulesHandler() {

}
/*
 * Main method that do all parsing before generating NFA and initialise all lists.
 */
void RulesHandler::init_rules() {
	string line;
	ifstream myfile ("domx.txt");
	if(!myfile.is_open())  cout << "Unable to open file";
	line = getline (myfile,line) ;
	while(line!=""){
		if(line.at(0)=='['){
			keyword.push_back(line);
			break;
		}
		else if(line.at(0)=='{'){
			punc.push_back(line);
			break;
		}
		else{
			for (int i = 0; i < line.length(); ++i) {
				if(line.at(i)==':'){
					pair <string,string> s (line.substr(0,i-1),line.substr(i+1,line.length()));
					regExp.push_back(s);
					break;
				}
				if(line.at(i)=='='){
					pair <string,string> s (line.substr(0,i-1),line.substr(i+1,line.length()));
					regDef.push_back(s);
					break;
				}

			}

		}
		line = getline (myfile,line) ;
	}
	  myfile.close();
}



RulesHandler::~RulesHandler() {
}

