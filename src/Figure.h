#ifndef FIGURE_H
#define FIGURE_H

#include "Color.h"
#include "Orientation.h"

class Figure{
public:
	Figure(Color color, bool cells[][], Orientation orientation);
	
private:
	Color color;
	bool cells[][];
	Orientation orientation;
}

#endif