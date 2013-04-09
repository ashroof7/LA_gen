/* 
 * File:   Graph.h
 * Author: Ahmed
 *
 * Created on April 6, 2013, 10:44 AM
 */
#ifndef GRAPH_H
#define	GRAPH_H

#include <vector>
#include <bitset>
#include <cstring>
#include "base.h"

using namespace std;

typedef bitset<MAX_IP> bs;
typedef pair<int, bs> pib;
typedef pair<bool, string> pis;
typedef vector<pib> vib;

class graph {
private:

public:
	vector<vib> adj_list;
	vector<pair<bool, string> > acceptance;
	graph();
	int size();
	int insert_node();
	void insert_edge(int from, int to, bs w, bool accepted, string pattern);
	void edge(int from, int to, bs w);
	pib get_edge(int from, int to);
	vib get_children(int node);
	vib* get_children_ptr(int node);
	vector<pis> get_acceptance();
	void print_graph(graph g);

};
#endif	/* GRAPH_H */

