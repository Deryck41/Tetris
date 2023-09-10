#ifndef GAME_H
#define GAME_H

#include "Figure.h"

#include <Windows.h>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

class GameField{
public:
	GameField(int width, int height);
	~GameField();
	void AddFigure(Figure figure);
	Figure GenerateFigure(Color color, Orientation orientation);
	void PlaceRandomFigureOnField();
	void DrawFigures();
	void TestDrawField();
	int GetWidth();
	int GetHeight();
private:
	std::vector<Figure> figures;
	Figure currentFigure;
	int width;
	int height;
};

#endif
