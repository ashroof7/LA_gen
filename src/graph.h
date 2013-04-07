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
typedef vector<pib> vib;


class graph {
private:
	vector<vib> v_graph;
	vector< pair <bool, string> > acceptance;

public:
	graph();
	int getLen();
	void insertNode();
	void insertEdge(int from, int to, char w, bool accepted, string pattern);
	vib get_children(int node);
	pib get_pair(int from, int to);

};
#endif	/* GRAPH_H */

