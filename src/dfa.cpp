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

	// initialize epsilon closure of all states
	for (int i = 0; i < v_graph.size(); i++) {
		state_closure.push_back(epsilon_closure(i));
	}

	// epsilon closure of first state
//	for (unsigned int i = 0; i < state_closure[0].size(); ++i) {
//		cout << state_closure[0][i] << endl;
//	}

}

void dfa::convert_to_dfa(graph &output) {
	// add start state
	output.insert_node();
	dfa_states[state_closure[0]] = 1;
	//    cout << state_closure[0].size() << endl;

	queue<vector<int> > q;
	q.push(state_closure[0]);
	int current_state = 1;
	while (!q.empty()) {
		vector<int> current_node = q.front();
		q.pop();
		// loop on the valid chars
		for (int i = 0; i < MAX_IP - 1; i++) {
			vector<int> under_input;
			// loop on the ndfa states
			for (unsigned int j = 0; j < current_node.size(); j++) {
				// loop on children of each state
				vib* children = v_graph.get_children(current_node[j]);
				for (unsigned int k = 0; k < (*children).size(); k++) {
					//					pib temp_pair = children[k];
					pib temp_pair ((*children)[k].first,(*children)[k].second);
					//                    if (temp_pair.second[getIndex(VALID_CHARS[i])] == 1) {
					if (temp_pair.second[i] == 1) {
						under_input.push_back(temp_pair.first);
						// merge the epsilon of the state and the under_input vector
						//                        cout << under_input.size() << endl;
						under_input.insert(under_input.end(),
								state_closure[temp_pair.first].begin(),
								state_closure[temp_pair.first].end());
						std::sort(under_input.begin(), under_input.end());
						for (unsigned int ll = 0; ll < under_input.size() - 1;
								ll++) {
							if (under_input[ll] == under_input[ll + 1]) {
								under_input.erase(under_input.begin() + ll);
								ll--;
							}
						}
						//                        cout << under_input.size() << endl;
					}
				}

			}

			//            cout << "abo isma3el" << endl;
			std::sort(under_input.begin(), under_input.end());

			// don't insert edge/node if under_input.size()==0
			if (dfa_states[under_input] == 0 && !under_input.empty()) {
				dfa_states[under_input] = output.size() + 1;

				output.insert_node();
				bs bitmap;
				//                bitmap.set(getIndex(VALID_CHARS[i]), 1);
				bitmap.set(i, 1);
				bool is_acc = false;
				string pattern = "";

				vector<pis>* accept_temp = v_graph.get_acceptance();
				for (unsigned int j = 0; j < under_input.size(); j++) {
					if ((*accept_temp)[under_input[j]].first) {
						is_acc = true;
						pattern = (*accept_temp)[under_input[j]].second;
						break;
					}
				}

				//                cout << dfa_states[current_node] << output.size() << endl;

				output.insert_edge(dfa_states[current_node] - 1,
						output.size() - 1, bitmap, is_acc, pattern);
				q.push(under_input);
			} else if (!under_input.empty()) {
				int next_state_num = dfa_states[under_input] - 1; // 3'ayarnaha
				bool edge_found = false;

				// neighbors
				vib* neighbors = output.get_children(current_state - 1);
				for (unsigned int j = 0 ; j< neighbors->size(); ++j){
					int m = (*neighbors)[j].first;
					if (m == next_state_num) {
						(*neighbors)[j].second[i] = 1;
						edge_found = true;
						break;
					}

				}

				if (!edge_found) {
					//                    output.adj_list[current_node-1].push_back(pib)
					bs bitset;
					bitset.set(i, 1);
//					pair<bool, string> state_acc;

//					state_acc.first = output.acceptance[dfa_states[under_input]	- 1].first;
//					state_acc.second = output.acceptance[dfa_states[under_input]- 1].second;

					vector<pis>* acc = output.get_acceptance();
					pis state_acc = (*acc)[dfa_states[under_input]-1];

					output.insert_edge(current_state - 1,
							dfa_states[under_input] - 1, bitset,
							state_acc.first, state_acc.second);
				}

			}
		}
		current_state++;
	}
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
		mask[n] = true;
		q.pop();
		vib* children = v_graph.get_children(n);
		for (unsigned int i = 0; i < (*children).size(); i++) {
			// edge (to, bitset)
			int child = (*children)[i].first;
			if ((*children)[i].second[EPSILON] == 1 && !mask[child]) {
				result.push_back(child);
				q.push(child);
				mask[child] = true;
			}
		}
	}
	std::sort(result.begin(), result.end());
	return result;
}
