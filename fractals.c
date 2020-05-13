/**
 * Assignment: PokeFractals
 * Class: UCSD CSE30-SP20
 */
#include <stdio.h>
#include <stdlib.h>

#include "fractals.h"

// return list of coordinates
int **recurse(int n)
{
    //Base case iteration 1
    if (n == 1)
    {
        int **points = memAlloc(n);
        //points[x][0] = row of point x
        //points[x][1] = col of point x
        points[0][0] = 0;
        points[0][1] = 0;
        points[1][0] = 1;
        points[1][1] = 0;
        points[2][0] = 2;
        points[2][1] = 0;
        points[3][0] = 3;
        points[3][1] = 1;
        points[4][0] = 3;
        points[4][1] = 0;
        points[5][0] = 1;
        points[5][1] = 1;
        points[6][0] = 2;
        points[6][1] = 2;
        points[7][0] = 3;
        points[7][1] = 2;
        points[8][0] = 3;
        points[8][1] = 3;
        return points;
    }
    else
    {
    
        int ** points = memAlloc(n);

        //Get subTriangle
        int **subPoints = recurse(n-1);
        int numSubPoints = numPoints(n-1);
        int numBase = basePoints(n-1);

        //Copy subtriangle to new board
        copyTriangle( points, subPoints, 0, 0, numSubPoints);
        //copy subtriangle with row offset equal to num of base points in triangle
        copyTriangle( (points+numSubPoints), subPoints, numBase, 0, numSubPoints);
        //copy subtriangle with row and col offset equal to num of base points in triangle
        copyTriangle( (points+2*numSubPoints), subPoints, numBase, numBase, numSubPoints);

        memFree(subPoints, numSubPoints);

        return points;
    }
}


/*
 * Allocates the required memory for the number of points
 */
int ** memAlloc(int iteration )
{
        int num = numPoints(iteration);

        int **points = (int **)malloc(sizeof(int *) * num);

        for (int i = 0; i < num; i++)
        {
            points[i] = malloc(sizeof(int) * 2);
        }
        
        return points;

}


/*
 * Frees all allocated memory in points
 */
void memFree( int ** points, int numPoints){
    for(int i = 0; i < numPoints; ++i){
        free(points[i]);
    }
    free(points);
}


/*
 * Returns the number of points of each triangle at iteration n
 */
int numPoints(int n)
{
    if (n == 1)
    {
        return 9;
    }
    else
    {
        return numPoints(n-1) * 3;
    }
}


/*
 * Returns the number of points in the base of the triangle at iteration n
 */
int basePoints(int n)
{
    if (n == 1)
    {
        return 4;
    }
    else
    {
        return basePoints(n-1)*2;
    }
    
}

/**
 * print the board in ascii
 */
int printAsciiFile(char * fileName){

    FILE *fp;
    //Check if file opened successfully
    if ((fp = fopen(fileName, "r")) == NULL){
      return -1;
    }

    //Get number of rows and columns
    int cols;
    int rows;

    fscanf(fp, "%d\n", &rows);
    fscanf(fp, "%d\n", &cols);

    unsigned char * buffer = calloc(rows * cols, sizeof(unsigned char));

    if( buffer == NULL){
      return -1;
    }
  
    //Read all coordinaes
    int x;
    int y;
    while(fscanf(fp, "%d %d", &x, &y) > 0){
      if(x > 0 && y > 0 && x < rows - 1 && y < cols - 1) {
        buffer[x*cols+y] = 1;
      }
    }

    //clear the screen
    printf("\033[2J");


    //Print all coordinates
    for (int i= 0; i<cols+2; i++){
      printf("=");
    }
    printf("\n");
    for (int  j=0; j<rows; j++){
      printf("|");
      for (int i=0; i<cols; i++){
        printf("%c", buffer[j*cols+i] ? '*' : ' ');
      }
      printf("|");
      printf("\n");

    }
    for (int i= 0; i<cols+2; i++){
      printf("=");
    }
    printf("\n");
    free(buffer);
    return 0;
}
