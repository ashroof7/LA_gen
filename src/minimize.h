#ifndef MINIMIZE_H_
#define MINIMIZE_H_

#include "graph.h"

namespace std {

class minimize {
public:
	int* class_of_states;
	vector<vector<int> > equivalent_classes;
	minimize(graph g);
	minimize();
	void update_classes();
	int get_class_under_input(int node, int char_index);
	void minimize_dfa();
	void build_minimized_dfa(graph& output);
	int get_start_node();
private:

};

} /* namespace std */
#endif /* MINIMIZE_H_ */
