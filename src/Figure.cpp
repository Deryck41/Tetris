#include "Figure.h"
#include "Color.h"
#include "Orientation.h"

Figure::Figure(Color color, bool cells[][], Orientation orientation){
	this->color = color;
	this->cells = cells;
	this->orientation = orientation;
}