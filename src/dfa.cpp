#include "graph.h"
#include "dfa.h"
#include "base.h"

using namespace std;

//vector<int> dfa::epsilon_closure(int node);

graph v_graph;
vector<vector<int> > state_closure;

dfa::dfa(graph gg) {
	v_graph = gg;

	// initialize epsilon closure of all states
	for (int i = 0; i < v_graph.getLen(); i++) {
		state_closure.push_back(epsilon_closure(i));
	}
}

vector<int> dfa::epsilon_closure(int node) {

	vector<int> result;
	queue<int> q;
	q.push(node);
	bool mask[v_graph.getLen()];

	for (int i = 0; i < v_graph.getLen(); i++) {
		mask[i] = false;
	}
	mask[node] = true;

	while (!q.empty()) {
		int n = q.front();
		q.pop();
		for (unsigned i = 0; i < v_graph.get_children(n).size(); i++) {
			pib edge = v_graph.get_pair(n, i);
			int child = edge.first;
			if (edge.second[EPISILON] == 1 && !mask[child]) {
				result.push_back(child);
				q.push(child);
				mask[child] = true;
			}
		}
	}
	return result;
}
