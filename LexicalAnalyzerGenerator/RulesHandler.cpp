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
#include <stack>


using namespace std;
RulesHandler::RulesHandler(const std::string &filename)
    : fileName(filename)  {
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

void RulesHandler::edit_expression_from_definition(){
    for (int i = 0; i < regDef.size(); ++i) {
        for (int j = i+1; j < regDef.size(); ++j) {
            replaceAll(regDef.at(j).second, regDef.at(i).first, regDef.at(i).second);
        }

    }
    for (int i = regDef.size()-1; i >= 0; --i) {
        for (int j = 0; j < regExp.size(); ++j) {
            replaceAll(regExp.at(j).second, regDef.at(i).first, regDef.at(i).second);
        }
    }
}

size_t RulesHandler::split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );
    return strs.size();
}

/* Main method that do all parsing before generating NFA and initialise all lists. */
void RulesHandler::init_rules() {
    string line;
    ifstream file (fileName);
    if(!file.is_open()){
        cout << "Unable to open file";
        return;
    }
    while(getline (file,line)){
        if(line.at(0)=='['){
            line=line.substr(1,line.length()-2);
            trim(line);
            add_in_symbol_table(line,"keyword");
            keyword.push_back(line);
        }
        else if(line.at(0)=='{'){
            line=line.substr(1,line.length()-2);
            trim(line);
            add_in_symbol_table(line,"punctuation");
            punc.push_back(line);
        }
        else{
            replaceAll(line, " ", "");
            replaceAll(line, "\\=", "=");
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
    }
    file.close();

    edit_expression_from_definition();
    for (int i = 0; i < regExp.size(); ++i) {
        regExp[i].second=infixToPostfix(regExp[i].second);
        cout<< regExp[i].first << " :" << regExp[i].second << endl;
    }
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
            temp=temp.substr(0, temp.length()-1);
            temp+=expand_seq(from,to);
            i++;
        }
        else temp+=line.at(i);
    }
    return temp;
}
void RulesHandler::add_in_symbol_table(string line,string type){
    vector<string> res;
    split( line, res, ' ' );
    for (int i = 0; i < res.size(); ++i) {
        replaceAll(res[i], "\\", "");
        Token token(type,res[i]);
        symbol_table.push_back(token);
    }
}
int  RulesHandler::getPrecedence(char c){

    switch (c) {
        case '(':
            return 1;
            break;
        case '|':
            return 2;
            break;
        case ' ':
            return 3;
            break;
        case '*':
            return 4;
            break;
        case '+':
            return 4;
            break;
        default:
            return 6;
            break;
    }
}
string RulesHandler::formatRegEx(string regex) {
    string res="";
    static const char arr[] = {'|','+','*'};
    vector<char> allOperators (arr, arr + sizeof(arr) / sizeof(arr[0]) );

    vector<char> binaryOperators('|');

    for (int i = 0; i < regex.length(); i++) {

        char c1 = regex.at(i);
        if (i + 1 < regex.length()) {
            char c2 = regex.at(i+1);

            res += c1;

            if (c1!='(' && c2!=')' && c2!='|' && c2!='*' &&
                c2!='+' && c1!='|'&& c1!='/'&& c2!='L' && c2!='+' && c2!='*') {
                res += ' ';
            }
        }
    }
    res += regex.at(regex.length() - 1);

    return res;
}

string RulesHandler::infixToPostfix(string regex) {
    string postfix = "";

    stack<char> mystack;

    string formattedRegEx = formatRegEx(regex);

    for (int i=0;i<formattedRegEx.length();i++) {
        switch (formattedRegEx[i]) {
            case '(':
                mystack.push(formattedRegEx[i]);
                break;

            case ')':
                while(mystack.top() != '(') {
                    postfix += mystack.top();
                    mystack.pop();
                }
                mystack.pop();
                break;

            default:
                while(mystack.size() > 0){
                    char peekedChar = mystack.top();

                    int peekedCharPrecedence = getPrecedence(peekedChar);
                    int currentCharPrecedence = getPrecedence(formattedRegEx[i]);

                    if (peekedCharPrecedence >= currentCharPrecedence) {
                        postfix += mystack.top();
                        mystack.pop();
                    } else {
                        break;
                    }
                }
                mystack.push(formattedRegEx[i]);
                break;
        }

    }
    while (mystack.size() > 0){
        postfix += mystack.top();
        mystack.pop();
    }
    return postfix;
}

RulesHandler::~RulesHandler() {
}
