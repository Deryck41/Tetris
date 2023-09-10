#include "Figure.h"

Figure::Figure(){}

Figure::Figure(Color color, bool cells[4][4], Orientation orientation, int x, int y){
	this->color = color;
	this->orientation = orientation;
	for (int i = 0; i < (sizeof(this->cells)/ sizeof(this->cells[0])); i++){
		for (int j = 0; j < (sizeof(this->cells[0]) / sizeof(this->cells[0][0])); j++){
			this->cells[i][j] = cells[i][j];
		}
	}
}

Color Figure::GetColor(){
	return color;
}

bool Figure::GetCell(int row, int col){
	return cells[row][col];
}


void Figure::Rotate(Orientation orientation){
	
}