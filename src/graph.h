/* 
 * File:   Graph.h
 * Author: Ahmed
 *
 * Created on April 6, 2013, 10:44 AM
 */
#ifndef GRAPH_H
#define	GRAPH_H

#include "base.h"

using namespace std;

class graph {
private:
	vector<vib> adj_list;
	vector<pair<bool, string> > acceptance;

public:
	graph();
	int size();
	int insert_node();
	void insert_edge(int from, int to, bs w, bool accepted, string pattern);
	void edge(int from, int to, bs w);
	void only_edge(int from, int to, bs w);
	void set_acceptance(int i, string s);
	pib get_edge(int from, int to);
	vib* get_children(int node);
	vib* get_children_ptr(int node);
	vector<pis>* get_acceptance();
	int append(graph* g);
	int append_to(graph &g);
	vector<vib>* get_adj_list();

	void print_graph();
	int get_state_under_input(int node, int input);

};
#endif	/* GRAPH_H */

