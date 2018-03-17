/*
 * RulesHandler.h
 *
 *  Created on: Mar 14, 2018
 *      Author: hosamelsafty
 */
#ifndef RULESHANDLER_H_
#define RULESHANDLER_H_
#include <string>
#include <stack>
#include <vector>


using namespace std;

class RulesHandler {
public:
	RulesHandler();
	vector<pair<string,string > >regExp;
	vector<pair<string,string > > regDef;
    vector<string>punc;
    vector<string>keyword;
    string expand_slash(string line);
    void edit_expression_from_definition();
    	string expand_seq(char from,char to);
    	void replaceAll(std::string& str, const std::string& from, const std::string& to) ;

    void init_rules();

    virtual ~RulesHandler();
private:

};


#endif /* RULESHANDLER_H_ */

