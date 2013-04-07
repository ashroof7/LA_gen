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
#include "dfa.h"

using namespace std;

//vector<int> dfa::epsilon_closure(int node);

graph v_graph;
vector< vector<int> > state_closure;

dfa::dfa(graph gg) {
	v_graph = gg;

	// initialize epsilon closure of all states
	for (int i = 0; i < v_graph.getLen() ; i++) {
		state_closure.push_back(epsilon_closure(i));
	}
}

vector<int> dfa::epsilon_closure(int node) {
	vector<int> result;
	queue<int> q;
	q.push(node);
	vector<bool> mask;
	for (int i = 0; i < v_graph.getLen(); i++) {
		mask.push_back(false);
	}
	mask[node] = true;

	while (!q.empty()) {
		int n = q.front();
		q.pop();
		for (unsigned i = 0; i < v_graph.get_children(n).size(); i++) {
			pair<int, char> p;
			p.first = v_graph.get_pair(n, i).first;
			p.second = v_graph.get_pair(n, i).second;
			if (p.second == v_graph.EPSILON && !mask[p.first]) {
				result.push_back(p.first);
				q.push(p.first);
				mask[p.first] = true;
			}
		}
	}
	return result;
}