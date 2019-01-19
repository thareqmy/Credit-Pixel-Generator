#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "point.h"



void getScreenInformation();
void initializeFrame();
void pixelBG(int height, int width, Color BGColor, char** fbp);
void paintPixel(char *fbp);

void arrayPointToFBP(Point* points, int N, Color pixelColor, char** fbp); 


//Global Frame Information
int fbfd;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long long screensize;
int xLoc;
int yLoc;
int currLoc;


int main()
{


    //Pixel Information
    //R, G, B, and Transparency FORMAT
    char *fbp = 0;

    initializeFrame();


    // Map the device to program
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    //Paint the pixel
    paintPixel(fbp);

    printf("The memory was painted to display successfully.\n");
    
    close(fbfd);
    return 0;
}

void getScreenInformation() {
    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }
}

void initializeFrame() {
    //Initialize Frame Information from Hardware Memory

    (fbfd) = 0;
    (screensize) = 0;

    // Open the file for reading and writing
    (fbfd) = open("/dev/fb0", O_RDWR);
    if ((fbfd) == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    getScreenInformation(fbfd);

    printf("%dx%d, %dbpp\n", (vinfo).xres, (vinfo).yres, (vinfo).bits_per_pixel);

    // Figure out the size of the screen in bytes
    (screensize) = (vinfo).xres * (vinfo).yres * (vinfo).bits_per_pixel / 8;

}

void pixelBG(int height, int width, Color BGColor, char** fbp) {
    //Get the pixel Screen and background color
    //Location
    int x, y;
    long int location;
    // Figure out where in memory to put the pixel
    for (y = yLoc; y < yLoc + height; y++) {
        for (x = xLoc; x < xLoc + width; x++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *((*fbp) + location) = BGColor.b;// Blue
                *((*fbp) + location + 1) = BGColor.g;// Green
                *((*fbp) + location + 2) = BGColor.r;// Red
                *((*fbp) + location + 3) = 0;      // No transparency
            
        //location += 4;
            } else  {
                //ni kaga penting gausah dimengerti
                int b = 10;
                int g = (x-100)/6;     // A little green
                int r = 31-(y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)((*fbp) + location)) = t;
            }
        }
    }


}

void paintPixel(char *fbp) {
    xLoc = 800;
    yLoc = 100;
    currLoc = 5;


    //Procedure to paint the pixel for display

    Color BGColor = {100, 100, 100};
    Color pixelColor = {255, 255, 255};
    char c[] = {'A','A','B','A','B','B'};
    int N;


    pixelBG(200, 200, BGColor, &fbp);
    for (int i = 0; i<6; i++) {
        Point* p = charToPoints(c[i], &N);
        arrayPointToFBP(p, N, pixelColor, &fbp);
    }



    munmap(fbp, screensize);

}
void arrayPointToFBP(Point* points, int N, Color pixelColor, char** fbp) {
    //Convert array of point to device FBP 

    long int location;

    for (int i = 0; i < N; ++i) {
        location = (points[i].x+vinfo.xoffset + xLoc + currLoc) * (vinfo.bits_per_pixel/8) +
                       (points[i].y+vinfo.yoffset + yLoc + 5) * finfo.line_length;

        if (vinfo.bits_per_pixel == 32) {
                *((*fbp) + location) = pixelColor.b;// Blue
                *((*fbp) + location + 1) = pixelColor.g;// Green
                *((*fbp) + location + 2) = pixelColor.r;// Red
                *((*fbp) + location + 3) = 0;      // No transparency
            
        //location += 4;
            } else  {
                //ni kaga penting gausah dimengerti
                int b = 10;
                int g = (points[i].x-100)/6;     // A little green
                int r = 31-(points[i].y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)((*fbp) + location)) = t;
            }
    }
    currLoc += 30;
} 