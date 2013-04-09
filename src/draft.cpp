/*
 * draft.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: Ashraf Saleh
 */

#include <iostream>
#include <stack>
#include "base.h"
#include "graph.h"
#include "reader.h"

using namespace std;

//void extract() {
//	graph g;
//	reader r;
//
//	char c;
//	r.open_file("input");
//
//	int src = g.add_node(), dest = g.add_node();
//
//	stack<int> s;
//	stack<int> e;
//	stack<int> st;
//	s.push(src);
//	e.push(dest);
//
//	// TODO move to base.h and make it global
//	bs eps;
//	eps[EPSILON] = 1;
//
//	int cur = 0,node,n1,n2;
//
//	// "aa(b(cd|ef)*)+"
//
//	while ((c = r.get_char()) != EOL_CHAR) {
//		cout<<c<<endl;
//		if (c == '(') {
//			st.push(cur);
//			src = g.add_node();
//			s.push(src);
//			dest = g.add_node();
//			e.push(dest);
//			cur = src;
//		} else if (c == ')') {
//			dest = e.top();
//			g.edge(cur, dest, eps);
//			cur  = dest;
//			if (is_closure(r.peek())) {
//				// nothig to do here
//				// logic at is_closure if
//			}else {
//				e.pop();
//				s.pop();
//			}
//
//		} else if (c == '|'){
//			g.edge(cur, e.top(), eps);
//			cur = s.top();
//		} else if (is_closure(c)) {
///*			       	|----------|
//			n1 -----|src   dest|----- n2
//					|----------|
//*/
//			n1 = g.add_node();
//			n2 = g.add_node();
//			src = s.top(); s.pop();
//			dest = e.top(); e.pop();
//
//			g.edge(n1, src, eps);
//			g.edge(cur, n2, eps);
//
//			if (c == '*') {
//				g.edge(dest, src, eps);
//				g.edge(n1, n2, eps);
//			} else if (c == '+') {
//				g.edge(dest, src, eps);
//			} else if (c == '?') {
//				g.edge(n1, n2, eps);
//			}
//
//			int prev_stop = st.top(); st.pop();
//			g.edge(prev_stop,n1,eps);
//			cur = n2;
//
//		} else {
//			bs b;
//			b[get_index(c)] = 1;
//
//			if (is_closure(r.peek())) {
//				// make a new subset and save the current node
//				st.push(cur);
//				src = g.add_node();
//				dest = g.add_node();
//				g.edge(src, dest, b);
//				s.push(src);
//				e.push(dest);
//			} else {
//
//				node = g.add_node();
//				g.edge(cur, node, b);
//				cur = node ;
//			}
//		}
//
//	}
//
//	//new line encountered
//	//TODO mark acceptance state
//	g.edge(cur,e.top(),eps);
//	s.pop(); e.pop();
//	cout<<g.size()<<endl;
//}

//void old(){
//	graph g;
//		stack<int> stack;
//		reader r;
//		r.open_file("input");
//		char c;
//		int current_node = 0;
//
//		// adding start and end nodes
//		g.add_node();
//		g.add_node();
//		stack.push(0);
//		stack.push(1);
//
//		// TODO move to base.h and make it global
//		bs eps;
//		eps[EPSILON] = 1;
//
//		string s = "aa(b(cd|ef)*)+";
//
//		int src_node, dest_node, temp;
//
//		while (true) {
//			c = r.get_char();
//			cout << c << endl;
//
//			if (c == '(') {
//				// insert 2 new nodes source and destination of the sub NFA
//				src_node = g.add_node();
//				dest_node = g.add_node();
//				stack.push(current_node);
//				stack.push(dest_node);
//				g.insert_edge(current_node, src_node, eps, false, "");
//			} else if (c == ')') {
//				dest_node = stack.top();
//				stack.pop();
//				g.insert_edge(current_node, dest_node, eps, false, "");
//				current_node = dest_node;
//
//			} else if (c == '|') {
//				// connect the last node in this branch with the top of the stack
//				dest_node = stack.top();
//				g.insert_edge(current_node, dest_node, eps, false, "");
//				stack.pop();
//				current_node = stack.top();
//				stack.push(dest_node);
//
//			} else if (c == '*') {
//
//				// insert 2 new nodes
//				int node1 = g.add_node();
//				int node2 = g.add_node();
//				g.insert_edge(node1, src_node, eps, false, "");
//	//            g.insertEdge(node1, node2,eps,false , "");
//				g.insert_edge(dest_node, node2, eps, false, "");
//				g.insert_edge(dest_node, src_node, eps, false, "");
//				g.insert_edge(temp, node1, eps, false, "");
//				dest_node = node2;
//				src_node = node1;
//
//			} else if (c == '+') {
//				// insert 2 new nodes
//				int node1 = g.add_node();
//				int node2 = g.add_node();
//				g.insert_edge(node1, src_node, eps, false, "");
//				g.insert_edge(dest_node, node2, eps, false, "");
//				g.insert_edge(dest_node, src_node, eps, false, "");
//				g.insert_edge(temp, node1, eps, false, "");
//				dest_node = node2;
//				src_node = node1;
//
//			} else if (c == '?') {
//				// insert 2 new nodes
//				int node1 = g.add_node();
//				int node2 = g.add_node();
//				g.insert_edge(node1, src_node, eps, false, "");
//				g.insert_edge(dest_node, node2, eps, false, "");
//				g.insert_edge(dest_node, src_node, eps, false, "");
//				g.insert_edge(node1, node2, eps, false, "");
//
//	//            g.insertEdge(temp, node1, eps, false, "");
//				dest_node = node2;
//				src_node = node1;
//
//			} else if (c == EOL_CHAR) {
//
//			} else {
//				// general case :: create new node and connect it to the current node
//				bs b;
//				b[get_index(c)] = 1;
//				dest_node = g.add_node();
//				cout << r.peek() << endl;
//				if (is_closure(r.peek())) {
//	//                temp = dest_node;
//					src_node = dest_node;
//				} else {
//					g.insert_edge(current_node, dest_node, b, false, "");
//				}
//
//				current_node = dest_node;
//
//				//TODO g.add(current_node, c+"");
//			}
//		}
//
//}

//int main() {
//	extract();
//		return 0;
//}

