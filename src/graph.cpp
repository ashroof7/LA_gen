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
	adj_list[from].push_back(pib(to, w));
	acceptance[to] = pis(false, "");
}

void graph::only_edge(int from, int to, bs w) {
	adj_list[from].push_back(pib(to, w));
}


void graph::set_acceptance(int i, string s){
	if (i < (int)  acceptance.size()){
		acceptance[i].first = true;
		acceptance[i].second = s;
	}
}

int graph::append_to(graph &g){
	// returns the index of the first node inserted
	int offset = g.size();
	for (unsigned int i = 0; i < adj_list.size(); ++i){
		g.insert_node();
//		cout<<i<<" "<<acceptance[i].first<<" "<<acceptance[i].second<<endl;
		if (acceptance[i].first)
			g.set_acceptance(i, acceptance[i].second);
	}
	for (unsigned int i = 0; i < adj_list.size(); ++i)
		for (unsigned int j = 0; j < adj_list[i].size(); ++j)
				g.only_edge(i+offset, adj_list[i][j].first+offset, adj_list[i][j].second);

	return offset ;
}


int graph::append(graph* g){

	vector<pis>* acc = g->get_acceptance();
	int offset = size();
	for ( int i = 0; i < g->size(); ++i){
			insert_node();
//			cout<<i<<" "<<acceptance[i].first<<" "<<acceptance[i].second<<endl;
			if ((*acc)[i].first)
				set_acceptance(i+offset, (*acc)[i].second);
		}

	for ( int i = 0; i < g->size(); ++i){
		vib* node = g->get_children(i);

		for (unsigned int j = 0; j < node->size(); ++j){
//			cout<<i<<" "<<j <<" "<< (*node)[j].first<< " "<<(*node)[j].second<<endl;
			adj_list[i+offset].push_back(pib((*node)[j].first+offset,(*node)[j].second));
		}
	}

	return offset;
}


vector<vib>* graph::get_adj_list(){
	return &adj_list;
}

vib * graph::get_children(int node) {
	return &(adj_list[node]);
}

pib graph::get_edge(int from, int to) {
	return adj_list[from][to];
}

vector<pis>* graph::get_acceptance() {
	return &acceptance;
}

vib *graph::get_children_ptr(int node) {
	return &adj_list[node];
}

void graph::print_graph() {
	for (int i = 0; i < size(); i++) {
		vib* vec = get_children(i);
		if (acceptance[i].first) {
			cout << acceptance[i].second <<"\t"<< i;
		} else {
			cout << "Non-Accept "<< i;
		}
cout<<"\t";

		for (unsigned int j = 0; j < vec->size(); j++) {
			cout << " " << (*vec)[j].first << " ";
			for (int k = 0; k < MAX_IP; k++)
				if ((*vec)[j].second[k] == 1)
					cout << VALID_CHARS[k] << " ";
//			cout<<(*vec)[j].second<<" ";
			cout << endl;
			cout<<"\t\t";
		}
		cout << endl;
	}

}

int graph::get_state_under_input(int node, int input_index) {
// loop on the graph, check bitset
	vib children = adj_list[node];

	for (unsigned int i = 0; i < children.size(); i++) {
		bs bits = children[i].second;
		if (bits[input_index] == 1)
			return children[i].first;
	}
	return -1; // no next state under this input
}
;
