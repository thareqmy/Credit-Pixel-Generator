#ifndef FRAME_H_
#define FRAME_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "point.h"
#include "color.h"

//Frame Data Structure
typedef struct {
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

} Frame;

void getScreenInformation(Frame* f);
void initializeFrame(Frame* f);
void arrayPointToFBP(Point* points, int N, Color pixelColor, Frame* f);

#endif