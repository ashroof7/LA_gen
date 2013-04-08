#include <algorithm>
#include "graph.h"
#include "dfa.h"
#include "base.h"

using namespace std;

graph v_graph;
vector<vector<int> > state_closure;
map<vector<int>, int> dfa_states;

dfa::dfa(graph gg) {
	v_graph = gg;

	int n = 0;
	vib child = v_graph.get_children(n);
	// initialize epsilon closure of all states
	for (int i = 0; i < v_graph.size(); i++) {
		state_closure.push_back(epsilon_closure(i));
	}

	// epsilon closure of first state
	for (unsigned int i = 0; i < state_closure[0].size(); ++i) {
		cout << state_closure[0][i] << endl;
	}

}

graph dfa::convert_to_dfa() {
	graph output;
	// add start state
	output.insertNode();
	dfa_states[state_closure[0]] = 1;
	cout << state_closure[0].size() << endl;

	queue<vector<int> > q;
	q.push(state_closure[0]);
	int current_state = 1;
	while (!q.empty()) {
		vector<int> current_node = q.front();
		q.pop();
		// loop on the valid chars
		for (int i = 0; i < MAX_IP; i++) {
			vector<int> under_input;
			// loop on the ndfa states
			cout << current_node.size() << endl;
			for (unsigned int j = 0; j < current_node.size(); j++) {
				cout << current_node[j] << endl;
				// loop on children of each state
				vib children = v_graph.get_children(current_node[j]);
				for (unsigned int k = 0; k < children.size(); k++) {
					pib temp_pair = children[k];
					if (temp_pair.second[getIndex(VALID_CHARS[i])] == 1) {
						under_input.push_back(temp_pair.first);
						// merge the epsilon of the state and the under_input vector
						cout << under_input.size() << endl;
						under_input.insert(under_input.end(),
								state_closure[temp_pair.first].begin(),
								state_closure[temp_pair.first].end());
						cout << under_input.size() << endl;
					}
				}

			}

			cout << "abo isma3el" << endl;
			std::sort(under_input.begin(), under_input.end());
			if (dfa_states[under_input] == 0) {
				dfa_states[under_input] = output.size() + 1;
				output.insertNode();
				bs bitmap;
				bitmap.set(getIndex(VALID_CHARS[i]), 1);
				bool is_acc = false;
				string pattern = "";

				vector<pair<bool, string> > accept_temp =
						v_graph.get_acceptance();
				for (unsigned int j = 0; j < under_input.size(); j++) {
					if (accept_temp[under_input[j]].first) {
						is_acc = true;
						pattern = accept_temp[under_input[j]].second;
					}
				}

				output.insertEdge(dfa_states[current_node], output.size() - 1,
						bitmap, is_acc, pattern);
				q.push(under_input);
			} else {
				int next_state_num = dfa_states[under_input];
				vib child_of_current_in_dfa = output.get_children(
						current_state - 1);

				for (unsigned int j = 0; j < child_of_current_in_dfa.size();
						j++) {
					pib edge_to = child_of_current_in_dfa[j];
					if (edge_to.first == next_state_num) {
						child_of_current_in_dfa[j].second.set(
								getIndex(VALID_CHARS[i]), 1);
						break;
					}
				}

			}
		}
		current_state++;

	}
	return output;
}

vector<int> dfa::epsilon_closure(int node) {
	vector<int> result;
	queue<int> q;
	q.push(node);
	bool mask[v_graph.size()];

	for (int i = 0; i < v_graph.size(); i++) {
		mask[i] = false;
	}
	mask[node] = true;

	while (!q.empty()) {
		int n = q.front();
		mask[n]=true;
		q.pop();
		vib children = v_graph.get_children(n);
		for (unsigned int i = 0; i < children.size(); i++) {
			// edge (to, bitset)
			pib edge;
			edge.first = children[i].first;
			edge.second = children[i].second;

			int child = children[i].first;
			if (edge.second[EPISILON] == 1 && !mask[child]) {
				result.push_back(child);
				q.push(child);
				mask[child] = true;
			}
		}
	}
	std::sort(result.begin(), result.end());
	return result;
}
