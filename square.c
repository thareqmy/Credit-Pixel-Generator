#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

void getScreenInformation(int fbfd, struct fb_var_screeninfo* vinfo, struct fb_fix_screeninfo* finfo) {
    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }
}

void initializeFrame(long long* screensize, int* fbfd, struct fb_var_screeninfo* vinfo, struct fb_fix_screeninfo* finfo) {
    //Initialize Frame Information from Hardware Memory

    (*fbfd) = 0;
    (*screensize) = 0;

    // Open the file for reading and writing
    (*fbfd) = open("/dev/fb0", O_RDWR);
    if ((*fbfd) == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    getScreenInformation((*fbfd), vinfo, finfo);

    printf("%dx%d, %dbpp\n", (*vinfo).xres, (*vinfo).yres, (*vinfo).bits_per_pixel);

    // Figure out the size of the screen in bytes
    (*screensize) = (*vinfo).xres * (*vinfo).yres * (*vinfo).bits_per_pixel / 8;

}

void paintPixel(char *fbp, long long screensize, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo) {
    //Procedure to paint the pixel for display

    //Location
    int x = 100, y = 100;
    long int location = 0;
    // Figure out where in memory to put the pixel
    for (y = 100; y < 300; y++) {
        for (x = 100; x < 300; x++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = 255;//100;        // Some blue
                *(fbp + location + 1) = 255;//15+(x-100)/2;     // A little green
                *(fbp + location + 2) = 255;//200-(y-100)/5;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
            
        //location += 4;
            } else  { //assume 16bpp
                int b = 10;
                int g = (x-100)/6;     // A little green
                int r = 31-(y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
        }
    }
    munmap(fbp, screensize);

}

int main()
{
    //Frame Information
    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long long screensize;


    //Pixel Information
    //R, G, B, and Transparency FORMAT
    char *fbp = 0;

    initializeFrame(&screensize, &fbfd, &vinfo, &finfo);


    // Map the device to program
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    //Paint the pixel
    paintPixel(fbp, screensize, vinfo, finfo);
    
    close(fbfd);
    return 0;
}