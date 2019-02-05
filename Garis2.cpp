#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

void Bresenham( float x1, float y1, float x2, float y2, string filename )
{
    // Bresenham's line algorithm

  ofstream myfile;
  myfile.open (filename);
  const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
  if(steep)
  {
    swap(x1, y1);
    swap(x2, y2);
  }
 
  if(x1 > x2)
  {
    swap(x1, x2);
    swap(y1, y2);
  }
 
  const float dx = x2 - x1;
  const float dy = fabs(y2 - y1);
 
  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int y = (int)y1;
 
  const int maxX = (int)x2;
 
  for(int x=(int)x1; x<=maxX; x++)
  {
    if(steep)
    {
        myfile << y << " " << x << "\n";
        cout << "x= " << y << " y= " << x << "\n";
    }
    else
    {
        myfile << x << " " << y << "\n";
        cout << "x= " << x << " y= " << y << "\n";
    }
 
    error -= dy;
    if(error < 0)
    {
        y += ystep;
        error += dx;
    }
  }
  myfile.close();
}

int main() {
    float x1,y1,x2,y2;
    cout << "Masukkan x1 y1" << "\n";
    cin >> x1;
    cin >> y1;
    cout << "Masukkan x2 y2" << "\n";
    cin >> x2;
    cin >> y2;
    Bresenham(x1,y1,x2,y2,"test2.txt");
    return 0;
}