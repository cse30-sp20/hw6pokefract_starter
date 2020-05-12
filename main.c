/**
 * Assignment: PokeFractals
 * Class: UCSD CSE30-SP20
 */
#include <stdio.h>
#include <stdlib.h>

#include "fractals.h"

int main(int argc, char * argv[])
{
    char * usage = "Usage:\n\n"  
                   "    ./fract [#iterations] [outputFile]    Generates new file with given number of iterations (#iterations > 0).\n"
                   "    ./fract [inputFile]                   Prints input file to terminal\n\n";
    //Print file
    if( argc == 2 ){
        if( printAsciiFile(argv[1]) == -1 ){
            fprintf(stdout, "Error. Could not open input file.\n%s", usage);
            return -1;
        }
        return 0;
            
    }
    if( argc != 3 ){
        fprintf(stdout, "%s\n", usage);
        return -1;
    }

    //Get number of iteration from input arguments
    int numIter = atoi(argv[1]);
    if( numIter < 1){
        fprintf(stdout, "Error. Number of iterations must be greater than 0.\n%s", usage);
        return -1;
    }

    int row = 1 << (numIter+1); 
    int col = row;

    FILE *fp;
    fp = fopen(argv[2], "w");
    fprintf(fp, "%d\n%d\n", row + 2, col + 2);

    //Get points/coordinates using number of points
    int num = numPoints(numIter);
    int **points = recurse(numIter);

    //Print points with offset 1 to avoid borders
    for (int i = 0; i < num; i++)
    {
        fprintf(fp, "%d %d\n", points[i][0] + 1, points[i][1] + 1);
    }
    memFree(points, num);
    fclose(fp);
    return 0;
}