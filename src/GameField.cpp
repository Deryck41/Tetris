
#include "GameField.h"
#include "Figure.h"
#include <iostream>

#define cellWidth 1
#define cellHeight 1

GameField::GameField(int width, int height){
	this->width = width;
	this->height = height;
}

int GameField::GetWidth(){
	return width;
}

int GameField::GetHeight(){
	return height;
}

void GameField::AddFigure(Figure figure){
	this->figures.push_back(figure);
}

void GameField::TestDrawField(){
	glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (float i = float(height); i > 0.0; i-=1.0) {
        glVertex2f(0.0, static_cast<float>(i));
        glVertex2f(static_cast<float>(width), static_cast<float>(i));
    }

    for (float i = float(width); i > 0; i-=1.0) {
        glVertex2f(static_cast<float>(i), 0.0);
        glVertex2f(static_cast<float>(i), static_cast<float>(height));
    }

    glEnd();
}

GameField::~GameField(){

}

Figure GameField::GenerateFigure(Color color, Orientation orientation) {
    // Здесь можно создать различные фигуры на основе заданных параметров
    // Например, создание фигуры "L" с определенным цветом и ориентацией:
    bool cells[4][4] = {
        {false, false, false, false},
        {false, false, false, false},
        {false, true, true, true},
        {false, true, false, false}
    };

    // Создание объекта Figure и его инициализация с заданными параметрами
    Figure figure(color, cells, orientation, 5, 15);

    // Возвращаем созданную фигуру
    return figure;
}

void GameField::PlaceRandomFigureOnField(){
	this->currentFigure = this->GenerateFigure(Color{1.0f, 0.0f, 0.0f}, Orientation::toLeft);
}

void GameField::DrawFigures(){
	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->currentFigure.GetCell(i,j)) { // Если клетка заполнена
                // Определите позицию и размер квадрата
                float x = j * cellWidth; // Здесь cellWidth - ширина одной клетки
                float y = i * cellHeight; // Здесь cellHeight - высота одной клетки
                Color currentColor = currentFigure.GetColor();
                // Установите цвет и отрисуйте квадрат
                glColor3f(currentColor.red, currentColor.green, currentColor.blue);
                glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + cellWidth, y);
                glVertex2f(x + cellWidth, y + cellHeight);
                glVertex2f(x, y + cellHeight);
                glEnd();
            }
        }
    }
}