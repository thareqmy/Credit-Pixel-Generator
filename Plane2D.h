#ifndef PLANE2D_H_
#define PLANE2D_H_
#include "Line.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXPOINT 500

//2DPLANE DATA STruCTURE

class Plane2D {
public:
	Line* lines;
	int lSize;
	int pSize;
	Point* points;

	//CCTOR
	Plane2D();
	Plane2D(char* filename);
	Plane2D(int l);
	Plane2D(Line* l, int ln);
	~Plane2D();

	void getEdgePoints(int* up, int* down, int* left, int* right);


};

#endif