/* 
 * File:   reader.h
 * Author: Amer
 *
 * Created on April 6, 2013, 12:27 PM
 */

#include <fstream>

using namespace std;

#ifndef READER_H
#define	READER_H

class reader {

private:
    ifstream file;
    string current_line;
    int current_size;
    int char_pointer;

public:
    reader();
    char peek();
    void open_file(string path);
    char get_char();
};
#endif	/* READER_H */

