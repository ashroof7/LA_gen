/* 
 * File:   Graph.h
 * Author: Ahmed
 *
 * Created on April 6, 2013, 10:44 AM
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

#define EPISOLON -1

#ifndef GRAPH_H
#define	GRAPH_H

//<node number, edge>
typedef vector<pair <int, char> > vii;

class graph {
private:
	vector<vii> v_graph;
	vector< pair <bool, string> > acceptance;
public:
	int EPSILON;

	graph();

	int getLen();
	void insertNode();
	void insertEdge(int from, int to, char w, bool accepted, string pattern);
	vector< pair<int, char> > get_children(int node);
	pair<int, char> get_pair(int from, int to);

};
#endif	/* GRAPH_H */

