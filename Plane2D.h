#ifndef PLANE2D_H_
#define PLANE2D_H_
#include "Line.h"

#define MAXPOINT 500

//2DPLANE DATA STruCTURE

class Plane2D {
	Line* lines;
	int lSize;
	int pSize;
	Point* points;

	//CCTOR
	Plane2D();
	Plane2D(int l);
	Plane2D(Line* l, int ln);


};

#endif