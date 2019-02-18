#include "Point.h"
#include "Line.h"
#include <iostream>

using namespace std;

//MAIN UNTUK TEST LINE.CPP
int main (){

    cout << "ini di dalam fungsi main\n";

    Line l(0,0,0,5);

    cout << l.getGradient() << endl;

    int arrsize;

    Point *arrPoints;
    arrPoints = new Point[100];

    arrPoints = l.getArrayOfPoints(&arrsize);

    for (int i=0;i<arrsize;i++){
        cout << "x: " << arrPoints[i].x << ", y: " << arrPoints[i].y << endl;
    }

    return 0;
}