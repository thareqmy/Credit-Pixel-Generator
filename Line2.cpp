#include "Line.h"

//CREATE CONS USING POINT
Line::Line(Point p1, Point p2) {
	this->p1 = p1;
	this->p2 = p2;
}

//CREATE CONS USING 4 INT as Point
Line::Line(int x1, int y1, int x2, int y2){
	Point a(x1, y1);
	Point b(x2, y2);
	this->p1 = a;
	this->p2 = b;
}

	//METHOD
double Line::getGradient() {
	double m = (p2.y-p1.y) / (p2.x- p1.x);
	return m;
}

	//convert line to points using bresenham
Point* Line::getArrayOfPoints() {
	double m = getGradient();
	if (m < 1) {
		int xmin = p1.x;
		int xmax = p2.x;
		Point *ptr[p2.x-p1.x];
		int j = 0;
		for (int i = xmin; i <= xmax; i++) {
			int y = (i*(p2.y-p1.y) - p1.x*(p2.y-p1.y) + p1.y*(p2.x-p1.x)) / (p2.x-p1.x);
			Point a(i,y);
			ptr[j] = &a;
			j++;
		}
	} else if (m > 1) {
		int ymin = p1.y;
		int ymax = p2.y;
		Point *ptr[p2.y-p1.y];
		int j = 0;
		for (int i = ymin; i <= ymax; i++) {
			int x = (i*(p2.x-p1.x) - p1.y*(p2.x-p1.x) + p1.x*(p2.y-p1.y)) / (p2.y-p1.y);
			Point a(x,i);
			ptr[j] = &a;
			j++;
		}
	}
	return ptr;
}