#include "frame.h"


void getScreenInformation(Frame* f) {
    // Get fixed screen information
    if (ioctl((*f).fbfd, FBIOGET_FSCREENINFO, &((*f).finfo)) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl((*f).fbfd, FBIOGET_VSCREENINFO, &((*f).vinfo)) == -1) {
        perror("Error reading variable information");
        exit(3);
    }
}
void initializeFrame(Frame *f) {
	//Initialize Frame Information from Hardware Memory

    ((*f).fbfd) = 0;
    ((*f).screensize) = 0;

    // Open the file for reading and writing
    

    ((*f).fbfd) = open("/dev/fb0", O_RDWR);
    if (((*f).fbfd) == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    getScreenInformation(f);

    printf("%dx%d, %dbpp\n", ((*f).vinfo).xres, ((*f).vinfo).yres, ((*f).vinfo).bits_per_pixel);

    // Figure out the size of the screen in bytes
    ((*f).screensize) = ((*f).vinfo).xres * ((*f).vinfo).yres * ((*f).vinfo).bits_per_pixel / 8;

}
void arrayPointToFBP(Point* points, int N, Color pixelColor, Frame *f) {

	//Convert array of point to device FBP 

    long int location;

    for (int i = 0; i < N; ++i) {
    	
        location = (points[i].x+((*f).vinfo).xoffset + (*f).xLoc + (*f).currLoc) * ((*f).vinfo.bits_per_pixel/8) +
                       (points[i].y+(*f).vinfo.yoffset + (*f).yLoc + 5) * (*f).finfo.line_length;

        if ((*f).vinfo.bits_per_pixel == 32) {
                *(((*f).fbp) + location) = pixelColor.b;// Blue
                *(((*f).fbp) + location + 1) = pixelColor.g;// Green
                *(((*f).fbp) + location + 2) = pixelColor.r;// Red
                *(((*f).fbp) + location + 3) = 0;      // No transparency
            
        //location += 4;
            } else  {

                //ni kaga penting gausah dimengerti
                int b = 10;
                int g = (points[i].x-100)/6;     // A little green
                int r = 31-(points[i].y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(((*f).fbp) + location)) = t;
            }
    }

    (*f).currLoc += 30;
} 