// C++ program for Bresenham’s Line Generation 
// Assumptions : 
// 1) Line is drawn from left to right. 
// 2) x1 < x2 and y1 < y2 
// 3) Slope of the line is between 0 and 1. 
//    We draw a line from lower left to upper 
//    right. 
#include <stdio.h>
#include <stdlib.h>

// function for line generation 
void bresenham(int x1, int y1, int x2, int y2, char* filename) 
{ 
	FILE *fp = NULL;
	int m_new = 2 * (y2 - y1); 
	int slope_error_new = m_new - (x2 - x1); 
	fp = fopen(filename, "w");

	for (int x = x1, y = y1; x <= x2; x++) { 
		fprintf(fp,"%d %d\n", x, y);
		// Add slope to increment angle formed 
		slope_error_new += m_new;

		// Slope error reached limit, time to 
		// increment y and update slope error. 
		if (slope_error_new >= 0) { 
		 	y++; 
			slope_error_new  -= 2 * (x2 - x1); 
		} 
	} 
	fclose(fp);
} 
  
void writeToFile(char* filename, int *data){
	FILE *fp = NULL;

	fp = fopen(filename, "w");
	for(int i = 0; i < sizeof(data)/sizeof(data[0]); i++){
		if (i%2 == 0){
			fprintf(fp, "%d ", data[i]);
		}
		fprintf(fp, "%d\n", data[i]);
	}
	fclose(fp);
}

void copyArray(int data[100][2], int *result[100]){
	for (int x = 0; x < 100; x++){
		*result[x] = data[x];
	}
}

// driver function 
int main() 
{ 
	int *data;
	int x_start;
	int y_start;
	int x_end;
	int y_end;

	printf("Masukan titik awal dan titik akhir garis : \n");
	scanf("%d", &x_start);
	scanf("%d", &y_start);
	scanf("%d", &x_end);
	scanf("%d", &y_end); 
	bresenham(x_start,y_start,x_end,y_end, "test.txt");
	return 0; 
} 