/*
 * test.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: leo
 */

#include <iostream>

#include <bitset>
#include "base.h"
#include "graph.h"
#include "dfa.h"

using namespace std;

void test_dfa() {
	graph g;
	g.insertNode();
	g.insertNode();
	g.insertNode();
	g.insertNode();
	g.insertNode();

	bs bitset1;
	bitset1.set(1, 1);

	g.insertEdge(0, 1, bitset1, false, "");
	g.insertEdge(0, 3, bitset1, false, "");

	bitset1.reset();
	bitset1.set('1', 1);

	g.insertEdge(1, 2, bitset1, true, "number");
	bitset1.reset();
	bitset1.set('a', 1);
	g.insertEdge(3, 4, bitset1, true, "id");

	dfa a(g);
	vector<int> res = a.epsilon_closure(0);
	for (unsigned int i = 0; i < res.size(); ++i) {
		cout << res[i] << endl;
	}
}
