/*
 * File:   simulator.cpp
 * Author: Korayyem
 *
 * Created on April 8, 2013
 */
#include "graph.h"
#include "base.h"
#include <sstream>
#include <iostream>

using namespace std;

void simulate(graph g, int start) {
	vector<pis>* acceptance = g.get_acceptance();
	ifstream file;
	string current_line;
	int current_size;
	int char_pointer;
	int line = 0;
	file.open("input.txt");
	char c;
	string maximal_match_pattern = "";
	string maximal_match_token = "";
	stringstream current_token;
	int after_maximal_match_pointer = 0;
	int current_node = start;
	while (!file.eof()) {
		getline(file, current_line);
		++line;
		current_size = current_line.length();
		char_pointer = 0;
		while (char_pointer < current_size) {
			bool found = false;
			c = current_line[char_pointer];

			//FIXME added ashraf
			if (c==' '){
				char_pointer++;
				continue;
			}

			vector<pib>* vib = g.get_children(current_node);
			for (unsigned int var = 0; var < (*vib).size(); ++var) {
				bs b = (*vib)[var].second;
				if (b[get_index(c)] == 1) {
					current_node = (*vib)[var].first;
					found = true;
					break;
				}
			}
			if (found) {
				++char_pointer;
				current_token << c;
				if ((*acceptance)[current_node].first) {
					maximal_match_pattern = (*acceptance)[current_node].second;
					maximal_match_token = current_token.str();
					after_maximal_match_pointer = char_pointer;
				}
			} else {
				if (maximal_match_token.compare("") == 0) {
					cout << "Error in line : " << line << " as character : "
							<< current_line[after_maximal_match_pointer] << " is not valid"
							<< endl;
					maximal_match_pattern = "";
					maximal_match_token = "";
					current_token.str("");
					++after_maximal_match_pointer;
					char_pointer = after_maximal_match_pointer;
					current_node = start;
				} else {
					cout << "Token : " << maximal_match_token
							<< " matches the lexeme of the pattern : "
							<< maximal_match_pattern << endl;
					maximal_match_pattern = "";
					maximal_match_token = "";
					current_token.str("");
					current_node = start;
					char_pointer = after_maximal_match_pointer;
				}
			}
		}
		if ((*acceptance)[current_node].first) { // match pattern with
			cout << "Token : " << maximal_match_token
					<< " matches the lexeme of the pattern : "
					<< maximal_match_pattern << endl;
			maximal_match_pattern = "";
			maximal_match_token = "";
			current_token.str("");
			current_node = start;
		} else {
			if (maximal_match_token.compare("") != 0) {
				cout << "Token : " << maximal_match_token
						<< " matches the lexeme of the pattern : "
						<< maximal_match_pattern << endl;
			}
			stringstream error;
			for (unsigned int k = after_maximal_match_pointer;
					k < current_line.length(); k++)
				error << current_line[k];

			cout << "Error in line : " << line << " as character : "
					<< error.str() << " is not valid" << endl;

		}
	}
}
//int main() {
//	graph g;
//
//	return 0;
//}
