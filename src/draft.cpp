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

int main() {
	graph g;
	stack<int> stack;
    reader r ;
    char c ;
    int current_node = 0;

    // adding start and end nodes
    g.insertNode();
    g.insertNode();
	stack.push(0);
    stack.push(1);


    // TODO move to base.h and make it global
    bs eps ;
    eps[EPSILON] = 1;


    string s = "aa(b(cd|ef)*)+";

    int src_node, dest_node, temp;

    while (true) {
        c = r.get_char();

		if (c == '(') {
            // insert 2 new nodes source and destination of the sub NFA
			src_node = g.insertNode();
            dest_node = g.insertNode();
            stack.push(current_node);
            stack.push(dest_node);
            g.insertEdge(current_node, src_node, eps, false, "");
        } else if(c== ')'){
            dest_node = stack.top();
            stack.pop();
            g.insertEdge(current_node, dest_node, eps, false, "");
            current_node = dest_node;

        } else if (c == '|'){
            // connect the last node in this branch with the top of the stack
            dest_node = stack.top();
            g.insertEdge(current_node, dest_node, eps, false, "");
            stack.pop();
            current_node = stack.top();
            stack.push(dest_node);

		} else if (c == '*') {

            // insert 2 new nodes
            int node1 = g.insertNode();
            int node2 = g.insertNode();
            g.insertEdge(node1, src_node,eps,false , "");
            g.insertEdge(node1, node2,eps,false , "");
            g.insertEdge(dest_node,node2,eps,false, "");
            g.insertEdge(dest_node, src_node,eps,false,"");
            g.insertEdge(temp, node1, eps, false, "");
            dest_node = node2;
            src_node = node1;

		} else if (c == '+') {
             // insert 2 new nodes
            int node1 = g.insertNode();
            int node2 = g.insertNode();
            g.insertEdge(node1, src_node,eps,false , "");
            g.insertEdge(dest_node,node2,eps,false, "");
            g.insertEdge(dest_node, src_node,eps,false,"");
            g.insertEdge(temp, node1, eps, false, "");
            dest_node = node2;
            src_node = node1;

    	} else if (c == '?') {
            // insert 2 new nodes
            int node1 = g.insertNode();
            int node2 = g.insertNode();
            g.insertEdge(node1, src_node,eps,false , "");
            g.insertEdge(node1, node2,eps,false , "");
            g.insertEdge(dest_node,node2,eps,false, "");
            g.insertEdge(temp, node1, eps, false, "");
            dest_node = node2;
            src_node = node1;

    	} else if (c == EOL_CHAR){

    	} else {
            // general case :: create new node and connect it to the current node
            bs b ;
            b[get_index(c)] = 1;
            dest_node = g.insertNode();
            if (! is_closure(r.peek()))
                g.insertEdge(current_node, dest_node, b, false, "");
            else
                temp = dest_node;

            src_node = current_node = dest_node;
            //TODO g.add(current_node, c+"");
    	}
	}
	return 0;
}







