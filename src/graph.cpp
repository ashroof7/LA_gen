#include "graph.h"
#include <iostream>

using namespace std;

graph::graph() {

}

int graph::size() {
	return adj_list.size();
}

int graph::insert_node() {
	adj_list.push_back(vib());
	acceptance.push_back(pis(false, ""));
	return adj_list.size() - 1;
}

void graph::insert_edge(int from, int to, bs w, bool accepted, string pattern) {
	adj_list[from].push_back(pib(to, w));
	acceptance[to] = pis(accepted, pattern);
}

void graph::edge(int from, int to, bs w) {
	//TODO does the other line must be here ??
	adj_list[from].push_back(pib(to, w));
}

vib graph::get_children(int node) {
	//TODO rename to get neighbors
	return adj_list[node];
}

pib graph::get_edge(int from, int to) {
	return adj_list[from][to];
}

vector<pis> graph::get_acceptance() {
	return acceptance;
}

vib *graph::get_children_ptr(int node) {
	return &adj_list[node];
}

void graph::print_graph(graph g) {
	for (int i = 0; i < g.size(); i++) {
		vib vec = g.get_children(i);
		cout << "Node " << i;
		for (unsigned int j = 0; j < vec.size(); j++) {
			pib my_pair = vec[j];
			cout << " goes to Node " << my_pair.first << " with chars ";
			for (int k = 0; k < MAX_IP; k++) {
				if (my_pair.second[k] == 1) {
					cout << VALID_CHARS[k] << " ";
				}
			}
			cout << endl;
		}
		cout << endl << endl;
	}

}
