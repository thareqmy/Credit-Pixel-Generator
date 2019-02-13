#include "Plane2D.h"
#include <iostream>

Plane2D::Plane2D(char* filename) {
	FILE *fp = NULL;
	fp = fopen(filename, "r");

	lines = new Line[20];
	points = new Point[MAXPOINT];
	lSize = 0;
	pSize = 0;

    

	

	while(!feof(fp)) {
		Point p1;
		Point p2;

		fscanf(fp, "%d", &lines[lSize].p1.x);
    	fscanf(fp, "%d", &lines[lSize].p1.y);

    	fscanf(fp, "%d", &lines[lSize].p2.x);
    	fscanf(fp, "%d", &lines[lSize].p2.y);

    	printf("%d %d %d %d\n", lines[lSize].p1.x , lines[lSize].p1.y , lines[lSize].p2.x , lines[lSize].p2.y );

    	int N;
    	Point* pTemps = lines[lSize].getArrayOfPoints(&N);
    	printf("%d\n", N);
    	for (int i = 0; i < N; i++) {
    		points[pSize].x = pTemps[i].x;
    		points[pSize].y = pTemps[i].y;
    		pSize++;
    	}
    	lSize++;
	}
	std::cout << "Uhiug";
    while(1<2) {}
}

Plane2D::Plane2D() {
	lSize = 1;
	pSize = 1;
	points = new Point[pSize];
	lines = new Line[lSize];
}

Plane2D::Plane2D(int l) {
	lSize = l;
	pSize =1;
	points = new Point[1];
	lines = new Line[lSize];
}

Plane2D::Plane2D(Line* l, int ln) {
	lSize = ln;
	lines = new Line[lSize];
	int N = 0;
	points = new Point[MAXPOINT];
	for (int i = 0; i<lSize; i++) {
		lines[i].p1.x = l[i].p1.x;
		lines[i].p1.y = l[i].p1.y;
		lines[i].p2.x = l[i].p2.x;
		lines[i].p2.y = l[i].p2.y;


		int NTemp;
		Point* pLine = l[i].getArrayOfPoints(&NTemp);
		for (int j = 0; j < NTemp; j++) {
			points[N].x = pLine[j].x;
			points[N].y = pLine[j].y;
			N++;
		}
	}
	pSize = N;
}


void Plane2D::getEdgePoints(int* up, int* down, int* left, int* right) {
	
	(*up)= points[0].y;
	(*down) = points[0].y;
	(*left) = points[0].x;
	(*right) = points[0].x;

	for (int i = 1; i < pSize; i++) {
		if (points[i].y > (*up) ) {
			(*up) = points[i].y;
		}
		if (points[i].y < (*down) ) {
			(*down) = points[i].y;
		}
		if (points[i].x > (*right) ) {
			(*right) = points[i].x;
		
		}
		if (points[i].x < (*left) ) {
			(*left) = points[i].x;
		}
	}
}

Plane2D::~Plane2D() {
	delete [] lines;
	delete [] points;
}
