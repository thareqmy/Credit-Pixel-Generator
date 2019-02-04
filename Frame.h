#ifndef FRAME_H_
#define FRAME_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "Point.h"
#include "Color.h"

#define XMAX 1300
#define YMAX 700
#define XMIN 25
#define YMIN 25

//Frame Data Structure
class Frame {
public:
	//Frame for  device
	int fbfd;

	//Variable information in device
	struct fb_var_screeninfo vinfo;

	//frame information in device
	struct fb_fix_screeninfo finfo;
	
	//Frame size
	long long screensize;
	

	//Esential information for frame
	int xLoc;
	int yLoc;
	int currLoc;
	
	//Where the pixel information mapped
	char* fbp;


	Frame();
	long long getLocationOnFrame(int x, int y);	
	void createBackground(Color c);


};


#endif