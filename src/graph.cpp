#include "graph.h"

using namespace std;

graph::graph() {

}

int graph::size() {
	return adj_list.size();
}

void graph::insertNode() {
	vib vector;
	adj_list.push_back(vector);

	pair<int, string> p;
	p.first = false;
	p.second = "";
	acceptance.push_back(p);
}

void graph::insertEdge(int from, int to, bs w, bool accepted, string pattern) {
	pib edge;
	edge.first = to;
	edge.second = w;
	adj_list[from].push_back(edge);

	pair<bool, string> p2;
	p2.first = accepted;
	p2.second = pattern;
	acceptance[to] = p2;
}

vib graph::get_children(int node) {
	return adj_list[node];
}

pib graph::get_pair(int from, int to) {
	return adj_list[from][to];
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

void graph::add(int from,string edge){
	// adds a new dest node and makes and edge from the source node to that node
	adj_list.push_back(vib());

	bs b ;
	for(unsigned int i = 0 ; i < edge.length(); i++)
		b[getIndex(edge[i])] = 1;

	adj_list[from].push_back(pib(adj_list.size()-1,b));
}
