
#include "GameField.h"
#include "Figure.h"
#include "Generator.h"

#include <stdlib.h>
#include <iostream>

#define cellWidth 1
#define cellHeight 1

GameField::GameField(int width, int height){
	this->width = width;
	this->height = height;
	this->movementSpeed = -0.0018f;
	this->virtualField = new bool*[this->height];

	for (int i = 0; i < this->height; i++){
	    this->virtualField[i] = new bool[this->width];
	    for (int j = 0; j < this->width; j++){
	        this->virtualField[i][j] = false;
	    }
	}

	this->loose = false;
}

GameField::~GameField(){
	// for (int i = 0; i < this->height; i++){
    //     delete[] virtualField[i];
    // }
    // delete[] virtualField;
}

int GameField::GetWidth(){
	return this->width;
}

int GameField::GetHeight(){
	return this->height;
}

bool GameField::GetLooseState(){
	return this->loose;
}


void GameField::TestDrawField(){
	glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (float i = float(this->height); i > 0.0; i-=1.0) {
        glVertex2f(0.0, static_cast<float>(i));
        glVertex2f(static_cast<float>(this->width), static_cast<float>(i));
    }

    for (float i = float(this->width); i > 0; i-=1.0) {
        glVertex2f(static_cast<float>(i), 0.0);
        glVertex2f(static_cast<float>(i), static_cast<float>(this->height));
    }

    glEnd();
}

void GameField::AddBlock(Block block){
	this->blocks.push_back(block);
}

void GameField::Update(float deltaTimeInSeconds){
	system("cls");

	for (int i = 0; i < this->height; i++){
		for (int j = 0; j < this->width; j++){
			if (this->virtualField[i][j]){
				std::cout << "*";
			}
			else{
				std::cout << "x";
			}
		}
		std::cout << std::endl;
	}

	this->currentFigure.ChangeY(deltaTimeInSeconds * this->movementSpeed);
	if (this->CheckCollisions()){
		this->ConvertFigureToBlocks();
		this->PlaceRandomFigureOnField();
	}
	this->CheckLines();
}

bool GameField::CheckCollisions(){
	int x = static_cast<int>(this->currentFigure.GetX());
	int y = static_cast<int>(this->currentFigure.GetY());

	for (int i = 3; i >= 0; i--){
		for (int j = 0; j < 4; j++){
			if (this->currentFigure.GetCell(i, j)){
				if (y - i == 0){
					return true;
				}
			}
		}
	}

	for (Block block : this->blocks){
		for (int i = 3; i >= 0; i--){
			for (int j = 0; j < 4; j++){
				if (this->currentFigure.GetCell(i, j)){
					if (x + j == block.GetX() && y - i == block.GetY()){
						return true;
					}
				}
			}
		}
	}

	return false;
}

 

void GameField::ConvertFigureToBlocks(){
	int x = static_cast<int>(this->currentFigure.GetX());
	int y = static_cast<int>(this->currentFigure.GetY());
	Color color = this->currentFigure.GetColor();

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (this->currentFigure.GetCell(i, j)){
				if (this->currentFigure.GetY() - i < this->height){
					Block block(x + j, y - i + 1, color);
					virtualField[y-i][x+j] = true;
					this->blocks.push_back(block);
				}
				else{
					this->loose = true;

				}
				
			}
		}
	}
}

Figure GameField::GenerateFigure(Color color, bool** cells, Orientation orientation) {

    Figure figure(color, cells, orientation, 5, 22);

    return figure;
}

void GameField::PlaceRandomFigureOnField(){
	this->currentFigure = this->GenerateFigure(GetRandomColor(), GetRandomFigureCells(), Orientation::toLeft);
}

void GameField::DrawFigures(){
	Color currentColor = this->currentFigure.GetColor();
	float x = this->currentFigure.GetX();
    float y = this->currentFigure.GetY();

    glColor3f(currentColor.red, currentColor.green, currentColor.blue);
    glBegin(GL_QUADS);

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (this->currentFigure.GetCell(i,j)){
				glVertex2f(static_cast<float>(x + j), static_cast<float>(y - i));
				glVertex2f(static_cast<float>(x + j + cellWidth), static_cast<float>(y - i));
				glVertex2f(static_cast<float>(x + j + cellWidth), static_cast<float>(y - i - cellHeight));
				glVertex2f(static_cast<float>(x + j), static_cast<float>(y - i - cellHeight));
			}
		}
	}

	for (Block block : this->blocks){
		currentColor = block.GetColor();
		int x = block.GetX();
		int y = block.GetY();
		glColor3f(currentColor.red, currentColor.green, currentColor.blue);

		glVertex2f(static_cast<float>(x), static_cast<float>(y));
		glVertex2f(static_cast<float>(x + cellWidth), static_cast<float>(y));
		glVertex2f(static_cast<float>(x + cellWidth), static_cast<float>(y - cellHeight));
		glVertex2f(static_cast<float>(x), static_cast<float>(y - cellHeight));
	}

    glEnd();
}

void GameField::CheckLines(){
	bool linesFilled[this->height];

	memset(linesFilled, false, sizeof(bool) * this->height);

	for (int i = 0; i < this->height; i++){
		int cellsFilled = 0;
		for (int j = 0; j < this->width; j++){
			if (virtualField[i][j]){
				cellsFilled++;
			}
		}
		if (cellsFilled == this->width){
			linesFilled[i] = true;
		}
	}

	this->ClearLines(linesFilled);
}

void GameField::ClearLines(bool linesFilled[]){
	std::cout << "Clear\n";
	for (int line = this->height - 1; line >= 0; line--){
		if (linesFilled[line]){
			for (int i = 0; i < this->blocks.size(); i++){
			    if (this->blocks[i].GetY() - 1 == line){
			        this->blocks.erase(this->blocks.begin() + i);
			        --i;
			    }
			}

			for (int i = 0; i < this->blocks.size(); i++){
				if (line + 1 < this->blocks[i].GetY()){
					this->blocks[i].ChangeY(-1);
				}
			}

			memset(virtualField[line], false, sizeof(bool) * this->width);

			for (int i = line + 1; i < this->height; i++){
				memcpy(virtualField[i - 1], virtualField[i], sizeof(bool) * this->width);
			}

			this->movementSpeed -= 0.0001;
		}
	}
}

void GameField::HandleMessage(MSG message){
	if (message.message == WM_KEYDOWN){
		switch(message.wParam){
			case VK_UP:
			case 0x57:
				this->currentFigure.Rotate();
				break;
			case VK_LEFT:
			case 0x41:
				this->currentFigure.ChangeX(-1);
				break;
			case VK_RIGHT:
			case 0x44:
				this->currentFigure.ChangeX(1);
				break;

		}
	}
}