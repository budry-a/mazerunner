/* utility.c
 * 
 * This file contains utility functions.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>

/*
 * Input: Fully generated maze, the rows and coloumns of the maze
 * Function: Display the maze 
 */
void print_maze(char** maze, int rows, int cols){
	int i, j;
	for(i = 0; i<rows; i++){
		for(j=0;j<cols;j++){
			printf("%c",*(*(maze+i)+j));
		}
		printf("\n");
	}
}

/*
 * Input: the maze and the number of rows
 * Function: free memory allocated for the maze
 */
void destroy_maze(char** maze, int rows){
	int i;
	for(i = 0; i < rows; i++){
		free(*(maze+i));
	}
	free (maze);
}

/*
 * Function: Clear standard input buffer
 */
void clearinputbuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return;
}
