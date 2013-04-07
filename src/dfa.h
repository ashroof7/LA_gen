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

#include "graph.h"

#ifndef DFA_H_
#define DFA_H_

class dfa
{
public:

	dfa(graph g);
    vector<int> epsilon_closure(int node);
};

#endif /*DFA_H_*/
