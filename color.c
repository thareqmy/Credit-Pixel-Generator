#include <stdlib.h>
#include <stdio.h>
#include "color.h"

Color randomRBG() {

	int r = rand() % 255;
	int b = rand() % 255;
	int g = rand() % 255;

	Color newColor = {r,b,g};
	return newColor;

}