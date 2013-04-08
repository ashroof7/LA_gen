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
	g.insertNode();
	g.insertNode();
	g.insertNode();
	g.insertNode();
	bs bitset;
	bitset.set(EPISILON, 1);
	g.insertEdge(0, 1, bitset, false, "");
	g.insertEdge(0, 4, bitset, false, "");
	g.insertEdge(0, 7, bitset, false, "");

	g.insertEdge(8, 7, bitset, false, "");

	bitset.reset();

	for (int i = 0; i < 10; i++)
		bitset.set(getIndex('0' + i), 1);
	g.insertEdge(7, 8, bitset, true, "One Or More Digit");

	bitset.reset();
	bitset.set(getIndex('E'), 1);
	g.insertEdge(4, 5, bitset, false, "");

	bitset.reset();
	bitset.set(getIndex('L'), 1);
	g.insertEdge(5, 6, bitset, true, "EL");

	bitset.reset();
	bitset.set(getIndex('I'), 1);
	g.insertEdge(1, 2, bitset, false, "");

	bitset.reset();
	bitset.set(getIndex('F'), 1);
	g.insertEdge(2, 3, bitset, true, "IF");

	dfa finite_state(g); /// ***********************************

	cout << "start here" << endl;
//	finite_state.convert_to_dfa();
	cout << "end" << endl;

//	graph g;
//	g.insertNode();
//	g.insertNode();
//	g.insertNode();
//	g.insertNode();
//	g.insertNode();
//
//	bs bitset1;
//	bitset1.set(1, 1);
//
//	g.insertEdge(0, 1, bitset1, false, "");
//	g.insertEdge(0, 3, bitset1, false, "");
//
//	bitset1.reset();
//	bitset1.set('1', 1);
//
//	g.insertEdge(1, 2, bitset1, true, "number");
//	bitset1.reset();
//	bitset1.set('31', 1);
//	g.insertEdge(3, 4, bitset1, true, "id");
//
//	dfa a(g);
//	vector<int> res = a.epsilon_closure(0);
//	for (unsigned int i = 0; i < res.size(); ++i) {
//		cout << res[i] << endl;
//	}

}

//int main() {
//test_dfa();
//return 0;
//}
