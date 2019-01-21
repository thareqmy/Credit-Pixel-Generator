#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/kd.h>
#include <string.h>
#include "point.h"
#include "color.h"
#include "frame.h"

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

int main()
{


    //Pixel Information
    //R, G, B, and Transparency FORMAT
    Frame currFrame;

    //int tty_fd = open("/dev/tty0", O_RDWR);
    //ioctl(tty_fd,KDSETMODE,KD_GRAPHICS);
    initializeFrame(&currFrame);


    // Map the device to program
    currFrame.fbp = (char *)mmap(0, currFrame.screensize, PROT_READ | PROT_WRITE, MAP_SHARED, currFrame.fbfd, 0);
    if ((int)currFrame.fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    //Paint the pixel

    paintPixel(fbp);
    for (y = 100; y < 100 + height; y++) {
        for (x = 100; x < 100 + width; x++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *((*fbp) + location) = BGColor.b;// Blue
                *((*fbp) + location + 1) = BGColor.g;// Green
                *((*fbp) + location + 2) = BGColor.r;// Red
                *((*fbp) + location + 3) = 0;      // No transparency


void paintPixel(char *fbp) {
    //Procedure to paint the pixel for display

    Color BGColor = {100, 100, 100};
    Color pixelColor = {0, 0, 0};
    Point apoints[625];
    Point bpoints[625];

    int count = 0;
    for (int i = 5; i < 25; i++) {
        for (int j = 0; j < 5; j++) {
            apoints[count] = {i, j};
            count++;
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 5; j < 15; j++) {
            apoints[count] = {i, j};
            count++;
        }
    }    
    for (int i = 5; i < 25; i++) {
        for (int j = 0; j < 5; j++) {
            apoints[count] = {i, j};
            count++;
        }
    }

    pixelBG(200, 200, BGColor, &fbp);
    arrayPointToFBP(points, 12, pixelColor, &fbp);



    munmap(fbp, screensize);

}
void arrayPointToFBP(Point* points, int N, Color pixelColor, char** fbp) {
    //Convert array of point to device FBP 

    long int location;

    for (int i = 0; i < N; ++i) {
        location = (points[i].x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (points[i].y+vinfo.yoffset) * finfo.line_length;

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
} 
