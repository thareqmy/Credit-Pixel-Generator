#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"

Point* charToPoints(char c, int* N) {
    FILE *fp;
    char filename[] = {'A', 'l', 'p', 'h', 'a', 'b', 'e', 't', '/', c, '.', 't', 'x', 't'};

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    (*N) = 0;
    Point* points = (Point*) malloc(625 * sizeof(points));

    while ((read = getline(&line, &len, fp)) != -1) {
        const char s[2] = ",";
        char *token;
        /* get the first token */
	   	token = strtok(line, s);
	   	
	   	int y = 0;
	   	int i = 0;
	   	while(token[i] != '\0') {
	   		y = y * 10;
	   		y = y + token[i] - '0';
	   		i++;
	   	}

	   	int x = 0;
	   	i = 0;
	   	/* walk through other tokens */
	   	
	   	token = strtok(NULL, s);

	   	while(token[i] != '\n') {
	   		x = x * 10;
	   		x = x + token[i] - '0';
	   		i++;
	   	}

	   	//printf("%d %d\n", x, y);
	   	points[(*N)].x = x;
	   	points[(*N)].y = y;
	   	(*N)++;


    }
    (*N)++;

    fclose(fp);
    
    return(points);
}

int charToInt(char* c, int N) {
	int i = 0;
	int num = 0;
	while (i < N || c[i] == ',') {
		num *= 10;
		num += c[i] - '0';
	}
	return num;
}