/*
 * parser.h
 *
 *  Created on: Apr 10, 2013
 *      Author: leo
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <stack>
#include "base.h"
#include "graph.h"

using namespace std;

#define trim(s) ((s).erase(0,(s).find_first_not_of(" \t")),	(s).erase((s).find_last_not_of(" \t")+1))

class parser {
private:
	graph build_NFA(const vector<string> &v, const string& label);
	void add_keyword(string s);

public:
	map<string, graph> classes;
	map<string, graph> RE;
	void read(istream &fin);
	void NFA(graph* g);
};

#endif /* PARSER_H_ */
