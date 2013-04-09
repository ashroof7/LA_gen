/*
 * test.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Ashraf Saleh
 */

#include <iostream>
#include <stack>
#include <bitset>

#include "base.h"
#include "graph.h"
#include "reader.h"
#include "dfa.h"



using namespace std;

graph extract() {
    graph g;
	reader r;

	char c;
	r.open_file("input");

	int src = g.insert_node(), dest = g.insert_node();

	stack<int> s;
	stack<int> e;
	stack<int> st;
	s.push(src);
	e.push(dest);

	// TODO move to base.h and make it global
	bs eps;
	eps[EPSILON] = 1;

	int cur = 0,node,n1,n2;

	// "aa(b(cd|ef)*)+"

	while ((c = r.get_char()) != EOL_CHAR) {
//		cout<<c<<endl;
		if (c == '(') {
			st.push(cur);
			src = g.insert_node();
			s.push(src);
			dest = g.insert_node();
			e.push(dest);
			cur = src;
		} else if (c == ')') {
			dest = e.top();
			g.edge(cur, dest, eps);
			cur  = dest;
			if (is_closure(r.peek())) {
				// nothig to do here
				// logic at is_closure if
			}else {
				e.pop();
				s.pop();
			}

		} else if (c == '|'){
			g.edge(cur, e.top(), eps);
			cur = s.top();
		} else if (is_closure(c)) {
/*			       	|----------|
			n1 -----|src   dest|----- n2
					|----------|
*/
			n1 = g.insert_node();
			n2 = g.insert_node();
			src = s.top(); s.pop();
			dest = e.top(); e.pop();

			g.edge(n1, src, eps);
			g.edge(cur, n2, eps);

			if (c == '*') {
				g.edge(dest, src, eps);
				g.edge(n1, n2, eps);
			} else if (c == '+') {
				g.edge(dest, src, eps);
			} else if (c == '?') {
				g.edge(n1, n2, eps);
			}

			int prev_stop = st.top(); st.pop();
			g.edge(prev_stop,n1,eps);
			cur = n2;

		} else {
			bs b;
			b[get_index(c)] = 1;

			if (is_closure(r.peek())) {
				// make a new subset and save the current node
				st.push(cur);
				src = g.insert_node();
				dest = g.insert_node();
				g.edge(src, dest, b);
				s.push(src);
				e.push(dest);
			} else {

				node = g.insert_node();
				g.edge(cur, node, b);
				cur = node ;
			}
		}

	}

	//new line encountered
	//TODO mark acceptance state
	g.edge(cur,e.top(),eps);
	s.pop(); e.pop();
        return g;
}


void test_dfa() {
//    graph g;
//    g.insertNode();
//    g.insertNode();
//    g.insertNode();
//    g.insertNode();
//    g.insertNode();
//    g.insertNode();
//    g.insertNode();
//    g.insertNode();
//    g.insertNode();
//    bs bitset;
//    bitset.set(EPISILON, 1);
//    g.insertEdge(0, 1, bitset, false, "");
//    g.insertEdge(0, 4, bitset, false, "");
//    g.insertEdge(0, 7, bitset, false, "");
//
//    g.insertEdge(8, 7, bitset, false, "");
//
//    bitset.reset();
//
//    for (int i = 0; i < 10; i++)
//        bitset.set(getIndex('0' + i), 1);
//    g.insertEdge(7, 8, bitset, true, "One Or More Digit");
//
//    bitset.reset();
//    bitset.set(getIndex('E'), 1);
//    g.insertEdge(4, 5, bitset, false, "");
//
//    bitset.reset();
//    bitset.set(getIndex('L'), 1);
//    g.insertEdge(5, 6, bitset, true, "EL");
//
//    bitset.reset();
//    bitset.set(getIndex('I'), 1);
//    g.insertEdge(1, 2, bitset, false, "");
//
//    bitset.reset();
//    bitset.set(getIndex('F'), 1);
//    g.insertEdge(2, 3, bitset, true, "IF");
    graph ana = extract();
    cout << ana.size();
    dfa finite_state(ana); /// ***********************************

    cout << "start here" << endl;
    graph outputt = finite_state.convert_to_dfa();
    cout << "end" << endl;
    cout << outputt.size() << endl;

    outputt.print_graph(outputt);


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

int main() {
    test_dfa();
    return 0;
}
