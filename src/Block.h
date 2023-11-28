#include "Color.h"

#ifndef BLOCK_H
#define BLOCK_H

struct Block{
public:
	Block(int x, int y, Color color);
	int GetX();
	int GetY();
	Color GetColor();
	void SetY(int value);
	void SetX(int value);
	void ChangeY(int value);
	void ChangeX(int value);
private:
	int x, y;
	Color color;
};

#endif // BLOCK_H