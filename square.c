#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "point.h"
#include "color.h"
#include "frame.h"


void pixelBG(int height, int width, Color BGColor, Frame* f);
void paintPixel(Frame *f);

int main()
{


    //Pixel Information
    //R, G, B, and Transparency FORMAT
    Frame currFrame;

    initializeFrame(&currFrame);


    // Map the device to program
    currFrame.fbp = (char *)mmap(0, currFrame.screensize, PROT_READ | PROT_WRITE, MAP_SHARED, currFrame.fbfd, 0);
    if ((int)currFrame.fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    //Paint the pixel
    paintPixel(&currFrame);

    printf("The memory was painted to display successfully.\n");
    
    close(currFrame.fbfd);
    return 0;
}

void pixelBG(int height, int width, Color BGColor, Frame* f) {
    //Get the pixel Screen and background color
    //Location
    int x, y;
    long int location;
    // Figure out where in memory to put the pixel
    for (y = (*f).yLoc; y < (*f).yLoc + height; y++) {
        for (x = (*f).xLoc; x < (*f).xLoc + width; x++) {
            location = (x+(*f).vinfo.xoffset) * ((*f).vinfo.bits_per_pixel/8) +
                       (y+(*f).vinfo.yoffset) * (*f).finfo.line_length;

            if ((*f).vinfo.bits_per_pixel == 32) {
                *(((*f).fbp) + location) = BGColor.b;// Blue
                *(((*f).fbp) + location + 1) = BGColor.g;// Green
                *(((*f).fbp) + location + 2) = BGColor.r;// Red
                *(((*f).fbp) + location + 3) = 0;      // No transparency
            
        //location += 4;
            } else  {
                //ni kaga penting gausah dimengerti
                int b = 10;
                int g = (x-100)/6;     // A little green
                int r = 31-(y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(((*f).fbp) + location)) = t;
            }
        }
    }


}

void paintPixel(Frame* f) {
    (*f).xLoc = 800;
    (*f).yLoc = 100;
    (*f).currLoc = 5;


    //Procedure to paint the pixel for display

    Color BGColor = {100, 100, 100};
    pixelBG(200, 200, BGColor, f);

    Color pixelColor = {255, 255, 255};
    char c[] = {'T','H','A','R','E','Q'};
    int N;


    
    for (int i = 0; i<6; i++) {
        Point* p = charToPoints(c[i], &N);
        arrayPointToFBP(p, N, pixelColor, f);
    }



    munmap((*f).fbp, (*f).screensize);

}