#include "graph.h"

using namespace std;

graph::graph() {

}

int graph::size() {
	return v_graph.size();
}

void graph::insertNode() {
	vib vector;
	v_graph.push_back(vector);

	pair<int, string> p;
	p.first = false;
	p.second = "";
	acceptance.push_back(p);
}

void graph::insertEdge(int from, int to, bs w, bool accepted, string pattern) {
	pib edge;
	edge.first = to;
	edge.second = w;
	v_graph[from].push_back(edge);

	pair<bool, string> p2;
	p2.first = accepted;
	p2.second = pattern;
	acceptance[to] = p2;
}

vib graph::get_children(int node) {
	return v_graph[node];
}

pib graph::get_pair(int from, int to) {
	return v_graph[from][to];
}

//TODO move to correct file & try to make it a macro
inline int getIndex(char x) {
	if (is_digit(x))
		return x - '0';
	if (is_lc_letter(x))
		return x - 'a' + 10;
	if (is_lc_letter(x))
		return x - 'A' + 36;
	return (strchr(VALID_SPECIAL_CHARS, x) - VALID_SPECIAL_CHARS) + 62;
}
