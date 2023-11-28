#include "Block.h"
#include <iostream>

Block::Block(int x, int y, Color color) : x(x), y(y), color(color){
}

int Block::GetX(){
	return this->x;
}

int Block::GetY(){
	return this->y;
}

Color Block::GetColor(){
	return this->color;
}

void Block::SetX(int value){
	this->x = value;
}

void Block::SetY(int value){
	this->y = value;
}

void Block::ChangeX(int value){
	this->x += value;
}

void Block::ChangeY(int value){
	this->y += value;
}