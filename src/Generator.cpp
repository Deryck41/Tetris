#include <stdlib.h>
#include <time.h>
#include <cstring>

#include "Generator.h"


Color GetRandomColor(){
	static bool isInitialized = false;
    if (!isInitialized) {
        srand(time(NULL));
        isInitialized = true;
    }

	Color colors[] = {
		{1.0f, 0.196f, 0.075f},
		{0.447f, 0.796f, 0.231f},
		{1.0f, 0.835f, 0.0f},
		{1.0f, 0.592f, 0.11f},
		{1.0f, 0.196f, 0.075f}
	};

	return colors[rand() % (sizeof(colors) / sizeof(Color))];
}

bool** GetRandomFigureCells(){
	static bool isInitialized = false;
    if (!isInitialized) {
        srand(time(NULL));
        isInitialized = true;
    }

	bool figures[5][4][4] = {
		{
	        {false, false, false, false},
	        {false, false, false, false},
	        {false, true, true, true},
	        {false, true, false, false}
    	},
    	{
    		{false, false, true, false},
    		{false, false, true, false},
    		{false, false, true, false},
    		{false, false, true, false}
    	},
    	{
    		{false, false, false, false},
    		{false, true, true, false},
    		{false, true, true, false},
    		{false, false, false, false}
    	},
    	{
    		{false, false, false, false},
    		{false, false, false, true},
    		{false, false, true, true},
    		{false, false, true, false}
    	},
    	{
    		{false, false, false, false},
    		{false, true, true, true},
    		{false, false, true, false},
    		{false, false, false, false}
    	}
	};

	short figuresLength = sizeof(figures)/ sizeof(figures[0]);

	bool*** figureCells = new bool**[figuresLength];

    for (int i = 0; i < figuresLength; i++) {
        figureCells[i] = new bool*[4];
        for (int j = 0; j < 4; j++) {
            figureCells[i][j] = new bool[4];
            memcpy(figureCells[i][j], figures[i][j], sizeof(bool) * 4);
        }
    }


	return figureCells[rand() % figuresLength];

}