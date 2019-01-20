#ifndef POINT_H_
#define POINT_H_

//Point Data Structure
typedef struct
{
    int x;
    int y;
} Point;

//Read file for a certai char and convert it to array point
Point* charToPoints(char c, int* N);
int charToInt(char* c, int N);


#endif