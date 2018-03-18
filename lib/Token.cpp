/*
 * Taken.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: hosamelsafty
 */


#include "Token.h"

#include <string>

using namespace std;

Token::Token(string t,string v) {
	type=t;
	value=v;
}

Token::~Token() {
}

