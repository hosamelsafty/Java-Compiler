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
	vector<pair<string,string>>regExp;
	vector<pair<string,string>>regDef;
    vector<string>punc;
    vector<string>keyword;



    void init_rules();

    virtual ~RulesHandler();
private:

};


#endif /* RULESHANDLER_H_ */

