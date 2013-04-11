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
#include "dfa.h"
#include "parser.h"
#include "minimize.h"
#include "simulator.h"

using namespace std;

int main() {
	bs eps;
	eps[EPSILON] = 1;
	ifstream fin;
//	fin.open("rules.txt");
	fin.open("in.txt");
	parser p;
	cout<<"Parser started"<<endl;
	p.read(fin);
	cout<<"Parser finished"<<endl<<endl;

	cout<<"NFA started"<<endl;
	graph NFA;
	p.NFA(&NFA);
//	NFA.print_graph();
	cout<<"NFA finished"<<endl<<endl;

	cout<<"DFA started"<<endl;
	dfa dfa_(NFA);
	graph DFA;
	dfa_.convert_to_dfa(DFA);
//	DFA.print_graph();
	cout<<"DFA finished"<<endl<<endl;

	cout<<"Minimization started"<<endl;
	graph MINI_DFA;
	minimize mini(DFA);
	mini.build_minimized_dfa(MINI_DFA);
	cout<<"Minimization finished"<<endl<<endl;

	cout<<"Simulation started"<<endl;
	simulate(MINI_DFA, mini.get_start_node());
	cout<<"Simulation finished"<<endl<<endl;

    return 0;
}
