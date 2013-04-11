#include "minimize.h"
#include <iostream>
#define ERROR_STATE -1

graph g;

minimize::minimize(graph gg) {
    g = gg;
    class_of_states = new int[g.size()];
    for (int i = 0; i < g.size(); i++) {
        class_of_states[i] = -1;
    }

    // initializes the vector <vector <int> > , // acceptance and non-acceptance
    vector<int> non_acceptance;

    vector<pis>* acc = g.get_acceptance();
    for (int i = 0; i < g.size(); i++) {
        if (!(*acc)[i].first) {
            non_acceptance.push_back(i);
        }
    }
    equivalent_classes.push_back(non_acceptance);

    bool entered_class[g.size()];
    for (int i = 0; i < g.size(); i++) {
        entered_class[i] = false;
    }

    for (int i = 0; i < g.size(); i++) {
        vector<int> temp;
        if ((*acc)[i].first && !entered_class[i]) {
            temp.push_back(i);
            entered_class[i] = true;
            for (int j = i + 1; j < g.size(); j++) {
                if ((*acc)[i].second == (*acc)[j].second && !entered_class[j]) {
                    temp.push_back(j);
                    entered_class[j] = true;
                }
            }
            equivalent_classes.push_back(temp);
        }
    }

    update_classes();
    minimize_dfa();
}

void minimize::minimize_dfa() { //
    // loop on all valid char
    for (int i = 0; i < MAX_IP - 1; i++) {
        // for on all classes in table
        for (unsigned int j = 0; j < equivalent_classes.size(); j++) {
            vector<vector<int> > partition;
            // loop to initialize output of partition
            for (unsigned int l = 0; l < equivalent_classes.size(); l++) {
                vector<int> v;
                partition.push_back(v);
            }

            vector<int> dummy;
            // loop inside each class
            for (unsigned int k = 0; k < equivalent_classes[j].size(); k++) {
                int next_state_class = get_class_under_input(
                        equivalent_classes[j][k], i);
                if (next_state_class != ERROR_STATE)
                    partition[next_state_class].push_back(
                        equivalent_classes[j][k]);
                else
                    dummy.push_back(equivalent_classes[j][k]);
                //					partition[j].push_back(equivalent_classes[j][k]);
            }

            int no_of_partitions = 0;
            for (unsigned int k = 0; k < partition.size(); k++) {
                if (!partition[k].empty())
                    no_of_partitions++;
            }
            if (!dummy.empty()) {
                no_of_partitions++;
            }
            if (no_of_partitions > 1) {
                equivalent_classes.erase(equivalent_classes.begin() + j); // remove original class
                j--;

                // insert partitions
                for (unsigned int k = 0; k < partition.size(); k++) {
                    if (!partition[k].empty())
                        equivalent_classes.push_back(partition[k]); // to be checked and replace with adding each integer integer
                }
                if (!dummy.empty())
                    equivalent_classes.push_back(dummy);
                update_classes();
            }
        }
    }

//	  print classes
//    for (unsigned int i = 0; i < equivalent_classes.size(); i++) {
//        cout << "class number " << i << " : ";
//        for (unsigned int j = 0; j < equivalent_classes[i].size(); j++) {
//            cout << equivalent_classes[i][j] << " , ";
//        }
//        cout << endl;
//    }
}

void minimize::build_minimized_dfa(graph& output) {
    vector<pis>* acc  = g.get_acceptance();
    for (unsigned int i = 0; i < equivalent_classes.size(); i++)
        output.insert_node();

    // loop for each class
    for (unsigned int i = 0; i < equivalent_classes.size(); i++) {
        // for each input
        vib* children = output.get_children(i);
        int node = equivalent_classes[i][0];
        for (int j = 0; j < MAX_IP - 1; j++) {
            int next_class = get_class_under_input(node, j);
            if (next_class == ERROR_STATE)
                continue;
            bool found = false;
            for (unsigned int k = 0; k < (*children).size(); k++) {
                if ((*children)[k].first == next_class) {
                    found = true; // we have edge
                    break;
                }
            }
            if (!found) {
                bs bits;
                bits.set(j, 1);
                pib new_edge(next_class, bits);


                int next_class_node = equivalent_classes[next_class][0];
                output.insert_edge(i, next_class, bits,
                        (*acc)[next_class_node].first,
                        (*acc)[next_class_node].first ?
                        (*acc)[next_class_node].second : "");

            } else {
                int to = 0;
//                vib child = output.get_children(i);
                for (unsigned int k = 0; k < (*children).size(); k++) {
                    if ((*children)[k].first == next_class) {
                        to = k;
                        break;
                    }
                }
                (*children)[to].second.set(j, 1);
            }
        }
    }
}

void minimize::update_classes() {
    for (unsigned int i = 0; i < equivalent_classes.size(); i++) {
        for (unsigned int j = 0; j < equivalent_classes[i].size(); j++) {
            class_of_states[equivalent_classes[i][j]] = i;
        }
    }
}

int minimize::get_class_under_input(int node, int char_index) {
    int next = g.get_state_under_input(node, char_index);
    if (next == -1) {
        return ERROR_STATE;
    } else
        return class_of_states[next];
}

int minimize::get_start_node(){
	return class_of_states[0];
}
