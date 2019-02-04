#include "Frame.h"



Frame::Frame() {
	//Initialize Frame Information from Hardware Memory

    fbfd = 0;
    screensize = 0;
    fbp = 0;

    // Open the file for reading and writing
    

    (fbfd) = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &(finfo)) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &(vinfo)) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", (vinfo).xres, (vinfo).yres, (vinfo).bits_per_pixel);

    // Figure out the size of the screen in bytes
    (screensize) = (vinfo).xres * (vinfo).yres * (vinfo).bits_per_pixel / 8;

    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
   /* if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }*/
    printf("The framebuffer device was mapped to memory successfully.\n");


}


long long Frame::getLocationOnFrame(int x, int y) {
    return((x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length);

}

void Frame::createBackground(Color c) {
    for (int i = XMIN ; i < XMAX; i++) {
        for (int j = YMIN ; j < YMAX; j++) {
            
            
            long long location = getLocationOnFrame(i,j);

            

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = c.b;        // Some blue
                *(fbp + location + 1) = c.g;     // A little green
                *(fbp + location + 2) = c.r;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
        //location += 4;
            } else  { //assume 16bpp
                int b = 10;
                int g = (i-100)/6;     // A little green
                int r = 31-(j-100)/16;    // A lot of red
                unsigned short int t = c.r<<11 | c.g << 5 | c.b;
                *((unsigned short int*)(fbp + location)) = t;
            }

        }
    }
}