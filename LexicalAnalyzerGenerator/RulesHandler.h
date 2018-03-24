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
#include "lib/Token.h"

using namespace std;

class RulesHandler {
    string fileName;
public:
    RulesHandler(const std::string &filename);
    vector<pair<string,string > >regExp;
    vector<pair<string,string > > regDef;
	vector<string> punc;
    vector<string>keyword;
    vector<string>  format_keyword(string line);
    string expand_score(string line);
    void edit_expression_from_definition();
    string expand_seq(char from,char to);
    void replaceAll(std::string& str, const std::string& from, const std::string& to) ;
    void add_in_vector(string line,string type);
    void init_rules();
    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
    string formatRegEx(string regex) ;
    int  getPrecedence(char c);
    string infixToPostfix(string regex) ;
    virtual ~RulesHandler();
private:

};


#endif /* RULESHANDLER_H_ */
