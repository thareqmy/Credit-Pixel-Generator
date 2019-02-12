#include "Plane2D.h"

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

