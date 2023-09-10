#ifndef FIGURE_H
#define FIGURE_H

#include "Color.h"
#include "Orientation.h"

class Figure{
public:
	Figure();
	Figure(Color color, bool cells[4][4], Orientation orientation, int x, int y);
	void Rotate(Orientation orientation);
	Color GetColor();
	bool GetCell(int row, int col);
	
private:
	Color color;
	bool cells[4][4];
	int x, y;
	Orientation orientation;
};

#endif //FIGURE_H