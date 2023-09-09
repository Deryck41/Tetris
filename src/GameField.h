#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

class GameField{
public:
	GameField(int width, int height);
	~GameField();
private:
	int width;
	int height;
}

#endif