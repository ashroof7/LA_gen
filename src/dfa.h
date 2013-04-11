#include  <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include "graph.h"

#ifndef DFA_H_
#define DFA_H_

class dfa {
public:
	dfa(graph g);
	vector<int> epsilon_closure(int node);
	void convert_to_dfa(graph& g);
};

#endif /*DFA_H_*/
