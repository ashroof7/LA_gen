/*
 * parser.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: leo
 */
#include "parser.h"
#include <algorithm>
#include <string>

#define toupper(s) (transform((s).begin(),(s).end(), (s).begin(), ::toupper))

graph parser::build_NFA(const vector<string> &v, const string &label) {

	string str;
	graph temp, g;
	char c;
	bs eps;
	eps[EPSILON] = 1;

	int src = g.insert_node(), dest = g.insert_node(), cur = g.insert_node();
	g.edge(src, cur, eps); // adding a dummy node at start
	src = cur;
	stack<int> s;
	stack<int> e;
	stack<int> st;
	s.push(src);
	e.push(dest);
	int node, n1, n2;

	for (unsigned int k = 0; k < v.size(); ++k) {
		str = v[k];
		c = str[0];

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
			cur = dest;
			if (k + 1 < v.size() && is_closure(v[k+1][0])) {
				// nothig to do here
				// logic at is_closure if
			} else {
				int prev_src = st.top();
				st.pop();
				g.edge(prev_src, s.top(), eps);
				e.pop();
				s.pop();
			}

		} else if (c == '|') {
			g.edge(cur, e.top(), eps);
			cur = s.top();
		} else if (is_closure(c)) {
			/*			       	|----------|
			 n1 -----|src   dest|----- n2
			 |----------|
			 */
			n1 = g.insert_node();
			n2 = g.insert_node();
			src = s.top();
			s.pop();
			dest = e.top();
			e.pop();

			g.edge(n1, src, eps);
			g.edge(dest, n2, eps);

			if (c == '*') {
				g.edge(dest, src, eps);
				g.edge(n1, n2, eps);
			} else if (c == '+') {
				g.edge(dest, src, eps);
			} else if (c == '?') {
				g.edge(n1, n2, eps);
			}

			int prev_stop = st.top();
			st.pop();
			g.edge(prev_stop, n1, eps);
			cur = n2;

		} else {
			if (classes.find(str) == classes.end()) {
				//is not defined before
				if (str.size() == 3 && str[1] == '-' && str[0] < str[2]) { //range
					bs b;
					for (int i = get_index(str[0]); i <= get_index(str[2]);
							++i) {
						b[i] = 1;
					}
					n1 = g.insert_node();
					n2 = g.insert_node();
					g.edge(n1, n2, b);
					g.edge(cur, n1, eps);
					cur = n2;
				} else {

					if (k + 1 < v.size() && is_closure(v[k+1][0])) {
						//next node is closure
						st.push(cur);
						src = g.insert_node();
						s.push(src);
						cur = src;
						dest = g.insert_node();
						e.push(dest);
					}

					for (unsigned int j = 0; j < str.length(); ++j) {
						c = str[j];
						if (c == '\\')
							continue;
						bs b;
						b[get_index(c)] = 1;
						node = g.insert_node();
						g.edge(cur, node, b);
						cur = node;
					}

				}

			} else {
				//defined before ---> copy nodes of that graph into the graph under construction
				int temp = g.size();
				n1 = classes[str].append_to(g);
				n2 = temp + 1;
				if (k + 1 < v.size() && is_closure(v[k+1][0])) {
					st.push(cur);
					s.push(n1);
					e.push(n2);
				} else {
					g.edge(cur, n1, eps);
				}
				cur = n2;

			}

		}

	}
	cout << label << endl;
	g.insert_edge(cur, e.top(), eps, true, label);
	src = s.top();
	s.pop();
	e.pop();

//	cout << "-----------" << endl;
//	g.print_graph();
//	cout << "-----------" << endl;
	return g;
}

void parser::add_keyword(string s) {
	graph g;
	int cur = g.insert_node();
	int temp;
	unsigned int i = 0;
	for (; i < s.length() - 1; ++i) {
		temp = g.insert_node();
		bs b;
		b[get_index(s[i])] = 1;
		g.edge(cur, temp, b);
		cur = temp;
	}
	temp = g.insert_node();
	bs b;
	b[get_index(s[i])] = 1;
	toupper(s);
	g.insert_edge(cur, temp, b, true, s);
	RE[s] = g;
}

void parser::read(istream &fin) {
	string label;
	char type;
	string s;

	while (getline(fin, s)) {
		if (s[s.length() - 1] == 13)
			s.erase(s.length() - 1);
		trim(s);
		stringstream ss;
		string temp;

		if (s[0] == '{') {
			// keywords line
			s.erase(0, 1);
			s.erase(s.length() - 1); //remove '{' and '}'

			ss.clear();
			ss.str(s);
			while (ss >> temp) {
				add_keyword(temp);
			}
		} else if (s[0] == '[') {
			// punctuation line
			s.erase(0, 1);
			s.erase(s.length() - 1); //remove '[' and ']'
			trim(s);
			ss.clear();
			ss.str(s);
			graph g;
			int src = g.insert_node();
			int dest  = g.insert_node();
			bs b;
			while (ss >> temp){
				cout<<temp<<endl;
				b[get_index(temp[0])] = 1;
			}
			g.insert_edge(src, dest, b, true, "Punctuation");
			g.print_graph();
			RE["Punctuation"] = g;
		} else {
			ss.clear();
			ss.str(s);
			ss >> label >> type;

			getline(ss, s);
			trim(s);
//			cout << s << endl;

			vector<string> tokens;
			unsigned int j = 0, i = 0;
			for (; i < s.length(); ++i) {
				if (s[i] == ' ' || s[i] == '\t') {
					if (i > j) {
						tokens.push_back(s.substr(j, i - j));
//						cout << "up "<<s.substr(j, i - j + 1) << endl;
					}
					j = i + 1;
				}else if (s[i]=='\\'){
					i++;

				} else if (strchr("()|*+?", s[i])
						&& (i == 0 || s[i - 1] != '\\')) {
					if (i - j > 0) //if not a space then push the last token from i to j
						tokens.push_back(s.substr(j, i - j));

					tokens.push_back(s.substr(i, 1));
//					cout << "do "<<s.substr(i, 1) << endl;
					j = i + 1;
				} else {

				}
			}

			if (j <= s.size() - 1)
				tokens.push_back(s.substr(j, s.size() - j));
//			print the vector
//			cout << "-----" << endl;
//			for (unsigned int i = 0; i < tokens.size(); i++)
//				cout << "$$ " << tokens[i] << endl;
//			cout << "------" << endl;

			graph g = build_NFA(tokens, label);

			if (type == '=') {
				// definition
				classes[label] = g;

			} else {
				// expression
				RE[label] = g;

			}

		}
	}
}

void parser::NFA(graph* g) {
	g->insert_node();
	bs eps;
	eps[EPSILON] = 1;
	for (map<string, graph>::iterator i = RE.begin(); i != RE.end(); ++i) {
		int cur = g->append(&(i->second));
		g->only_edge(0, cur, eps);
	}

}
