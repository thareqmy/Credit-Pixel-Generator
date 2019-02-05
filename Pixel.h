#ifndef PIXEL_H_
#define PIXEL_H_
#include "Point.h"
#include "Color.h"
#include "Frame.h"

//Pixel Data Structure
class Pixel {
public:
	//ATR
	Point PPoint;
	Color PColor;

	//COns
	Pixel();
	Pixel(Point PPoint, Color PColor);
	Pixel(int x, int y, int r, int g, int b);

	//METHOF
	void pixelToFrame(Frame *f);
	

};

#endif