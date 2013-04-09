/* 
 * File:   reader.cpp
 * Author: Amer
 * 
 * Created on April 6, 2013, 12:27 PM
 */

#include "reader.h"
#include "base.h"

reader::reader() {
	current_size = 0;
	char_pointer = 0;
	first_read = true;
}

void reader::open_file(string path) {
	file.open(path.c_str());

}

char reader::peek() {
	return current_line[char_pointer];
}

char reader::get_char() {
	if (char_pointer >= current_size) {
		if (!file.eof()) {
			getline(file, current_line);
			current_size = current_line.length();
			char_pointer = 0;

			if (first_read) {
				first_read = false;
				return current_line[char_pointer++];
			}
			return EOL_CHAR;

		} else {
			return -1;
		}
	}
	return current_line[char_pointer++];
}
