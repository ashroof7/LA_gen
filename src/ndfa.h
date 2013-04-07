/* 
 * File:   ndfa.h
 * Author: Ahmed
 *
 * Created on April 6, 2013, 12:27 PM
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

#ifndef NDFA_H
#define	NDFA_H

class reader {
private:
    ifstream file;
    string current_line;
    int current_size;
    int char_pointer;
public:
    reader();
    void open_file(string path);
    char get_char();
};
#endif	/* NDFA_H */

