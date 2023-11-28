#ifndef GAME_H
#define GAME_H

#include "Figure.h"
#include "Block.h"

#include <Windows.h>
#include <vector>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>

class GameField{
public:
	GameField(int width, int height);
	~GameField();
	Figure GenerateFigure(Color color, bool** cells, Orientation orientation);
	void PlaceRandomFigureOnField();
	void DrawFigures();
	void TestDrawField();
	int GetWidth();
	int GetHeight();
	void Update(float movementSpeed);
	void HandleMessage(MSG message);
	bool GetLooseState();
private:
	std::vector<Block> blocks;
	Figure currentFigure;
	int width;
	int height;
	float movementSpeed;
	bool loose;
	bool **virtualField;
	bool CheckCollisions();
	void ConvertFigureToBlocks();
	void AddBlock(Block block);
	void CheckLines();
	void ClearLines(bool linesFilled[]);
};

#endif
