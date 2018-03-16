/*
 * RulesHandler.cpp
 *
 *  Created on: Mar 14, 2018
 *      Author: hosamelsafty
 */


#include "RulesHandler.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

RulesHandler::RulesHandler() {

}
string expand_seq(char from,char to){
	int f=(int)from;
	int t=(int)to;
	string temp="(";
	for (int i = f; i <= t; ++i) {
		temp+=(char)i;
		temp+='|';
	}
	temp.at(temp.length()-1)=')';
	return temp;
}
string expand_slash(string line){

		string temp="";
		for (int i = 0; i < line.length(); ++i) {

			if(line.at(i)=='-'){

				char from=line.at(i-1);
				char to=line.at(i+1);
				temp=temp.substr(0, temp.length()-1);
				cout<<temp<<"\n";
				temp+=expand_seq(from,to);
				i++;
			}
			else temp+=line.at(i);
			cout<<"teemp::"<<temp<<endl;
		}
return temp;
}
/*
 * Main method that do all parsing before generating NFA and initialise all lists.
 */
void RulesHandler::init_rules() {

	string line;
	ifstream myfile ("domx.txt");
	if(!myfile.is_open())  cout << "Unable to open file";
	 getline (myfile,line) ;
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
					string exp_name=line.substr(0,i-1);
					cout<<"sub line :"<<line.substr(i+1,line.length())<<endl;
					string regular_expanded=expand_slash(line.substr(i+1,line.length()));
					cout<<"after expand :"<<regular_expanded<<endl;
					pair <string,string> s (exp_name,regular_expanded);
					regDef.push_back(s);
					break;
				}

			}

		}
		getline (myfile,line) ;
	}
	  myfile.close();

}


RulesHandler::~RulesHandler() {
}

