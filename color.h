#ifndef _COLOR_H
#define _COLOR_H

#include <iostream>

enum Color {
	Red, Black};

std::ostream & operator<<(std::ostream &out, Color & c) {
	const static char* color[2] = {"R", "B"};
	out << color[c]; 
	return out;
}

#endif
