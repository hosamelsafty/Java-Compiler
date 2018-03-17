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
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
using namespace std;

RulesHandler::RulesHandler() {

}



// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

void RulesHandler::edit_expression_from_definition(){//TODO R T
	for (int i = 0; i < regDef.size(); ++i) {
		for (int j = 0; j < regExp.size(); ++j) {
//			cout<<"before::"<<regExp.at(j).second<<endl;
			replaceAll(regExp.at(j).second, regDef.at(i).first, regDef.at(i).second);
//			cout << regExp.at(j).second<<endl;
//			cout<<"after::"<<regExp.at(j).second<<endl;
		}
	}
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
			line=line.substr(1,line.length()-2);
			trim(line);
			keyword.push_back(line);
			break;
		}
		else if(line.at(0)=='{'){
			line=line.substr(1,line.length()-2);
			trim(line);
			punc.push_back(line);
			break;
		}
		else{
			replaceAll(line, " ", "");
			for (int i = 0; i < line.length(); ++i) {
				if(line.at(i)==':'){
					pair <string,string> temp (line.substr(0,i),line.substr(i+1,line.length()));

					regExp.push_back(temp);
					break;
				}
				if(line.at(i)=='='){
					string exp_name=line.substr(0,i);
					string regular_expanded=expand_slash(line.substr(i+1,line.length()));

					pair <string,string> temp (exp_name,regular_expanded);
					regDef.push_back(temp);
					break;
				}

			}

		}
		getline (myfile,line) ;
	}
	  myfile.close();

	  edit_expression_from_definition();

}
void RulesHandler::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

string RulesHandler::expand_seq(char from,char to){
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
string RulesHandler::expand_slash(string line){

		string temp="";
		for (int i = 0; i < line.length(); ++i) {

			if(line.at(i)=='-'){
				char from=line.at(i-1);
				char to=line.at(i+1);
//				cout<<"before::"<<from<<" "<<to<<endl;
//				cout<<"before::"<<temp<<endl;
				temp=temp.substr(0, temp.length()-1);
				temp+=expand_seq(from,to);
//				cout<<"after::"<<temp<<endl;
				i++;
			}
			else temp+=line.at(i);
		}
return temp;
}

RulesHandler::~RulesHandler() {
}

