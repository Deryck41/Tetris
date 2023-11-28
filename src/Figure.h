#ifndef FIGURE_H
#define FIGURE_H

#include "Color.h"
#include "Orientation.h"

class Figure{
public:
	Figure();
	Figure(Color color, bool** cells, Orientation orientation, int x, int y);
	void Rotate();
	Color GetColor();
	bool GetCell(int row, int col);
	int GetX();
	int GetY();
	void ChangeX(float value);
	void ChangeY(float value);
	
private:
	Color color;
	bool cells[4][4];
	float x, y;
	Orientation orientation;
};

#endif //FIGURE_H