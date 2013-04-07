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
#include "graph.h"

using namespace std;

graph::graph() {
	EPSILON= -1;
}

int graph::getLen() {
	return v_graph.size();
}

void graph::insertNode() {
	vii vector;
	v_graph.push_back(vector);

	pair<int, string> p;
	p.first=false;
	p.second = "";
	acceptance.push_back(p);
}

void graph::insertEdge(int from, int to, char w, bool accepted, string pattern) {
	pair <int, char> p1;
	p1.first = to;
	p1.second = w;
	v_graph[from].push_back(p1);

	pair <bool, string> p2;
	p2.first = accepted;
	p2.second = pattern;
	acceptance[to] = p2;
}

vector< pair<int, char> > graph::get_children(int node) {
	return v_graph[node];
}

pair<int, char> graph::get_pair(int from, int to) {
	return v_graph[from][to];
}