#include <stdio.h>
#include <stdlib.h>

// return list of coordinates
int **recurse(int);

/*
 * Returns the number of points of each triangle at iteration n
 */
int numPoints(int);

/*
 * Returns the number of points in the base of the triangle at iteration n
 */
int basePoints(int n);

/*
 * Allocates the required memory for the number of points
 */
int ** memAlloc(int iteration );

/*
 * Frees all allocated memory in points
 */
void memFree( int ** points, int numPoints);

/*
 * Copies the given triangle into the appropriate position
 */
void copyTriangle(int ** startPoint, int ** subPoints, int rowOffset, int colOffset, int numSubPoints );

/*
 * Prints the inputfile to terminal
 */
int printAsciiFile(char * fileName);
