#ifndef POINT_H_
#define POINT_H_

//Point Data Structure
typedef struct
{
    int x;
    int y;
} Point;


//RGB Data Structure
typedef struct
{
    int r;
    int g;
    int b;
} Color;

//Read file for a certai char and convert it to array point
Point* charToPoints(char c);

#endif