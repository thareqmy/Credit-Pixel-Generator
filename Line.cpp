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
	p1 = a;
	p2 = b;
}

	//METHOD
double Line::getGradient() {
	double m = (y2-y1) / (x2- x1);
	return m;
}

	//convert line to points using bresenham
Point* Line::getArrayOfPoints() {

}