#include "Figure.h"

Figure::Figure(){}

Figure::Figure(Color color, bool** cells, Orientation orientation, int x, int y){
	this->color = color;
	this->orientation = orientation;

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			this->cells[i][j] = cells[i][j];
		}
	}

	this->x = (float)x;
	this->y = (float)y;
}

int Figure::GetX(){
	return this->x;
}

int Figure::GetY(){
	return this->y;
}

Color Figure::GetColor(){
	return this->color;
}

void Figure::ChangeX(float value){

	if (value > 0){
		for (int j = 3; j >= 0; j--){
			for (int i = 0; i < 4; i++){
				if (this->cells[i][j] && x + j + 1 == 10){
					return;
				}
			}
		}
	}
	else{
		for (int j = 0; j < 4; j++){
			for (int i = 0; i < 4; i++){
				if (this->cells[i][j] && x + j == 0){
					return;
				}
			}
		}
	}
	this->x += value;
}

void Figure::ChangeY(float value){
	this->y += value;
}

bool Figure::GetCell(int row, int col){
	return this->cells[row][col];
}


void Figure::Rotate(){

    for (int i = 0; i < 2; i++) {
        for (int j = i; j < 4 - i - 1; j++) {
            int temp = cells[i][j];
            cells[i][j] = cells[3 - j][i];
            cells[3 - j][i] = cells[3 - i][3 - j];
            cells[3 - i][3 - j] = cells[j][3 - i];
            cells[j][3 - i] = temp;
        }
    }
}