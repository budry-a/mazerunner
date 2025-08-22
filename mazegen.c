/* mazegen.c
 * 
 * This file generates a maze.
 *
 * CST8234 Assignment 1: Maze Runner
 * Student name: Budry Ahmed
 * Student number: 040801692
 */
 
#include <stdio.h>
#include <stdlib.h>

#define MAX_PATH_FAILURES 1000

static void generate_maze(char** maze, int rows, int cols);
static int make_path(char** maze, int rows, int cols);

/*
 * Input: rows and coloumns for the maze
 * Return: 2 dimensional array representing the maze, or NULL if creating maze was unsuccessful
 * Function: Create the maze
 */
char** create_maze(int rows, int cols){
	char** maze = NULL;
	int i, j;
	int valid_path;
	/*Allocate memory for the rows*/
	maze = malloc(sizeof(char*)*rows);
	if(maze==NULL){
		printf("malloc error\n");
		return NULL;
	}
	/*Allocate memory for the columns*/
	for(i = 0; i < rows; i++){
		*(maze+i) = malloc(sizeof(char)*cols);
		if(*(maze+i)==NULL){
			printf("row malloc error\n");
			/*Free memory for previously allocated rows upon failure*/
			for(j = 0; j < i; j++){
                free(*(maze+j)); 
            }
            free(maze);
			return NULL;
		}
	}
	/*Generate walls, start and exit points, and valid path*/
	do {
		generate_maze(maze, rows, cols);
		valid_path = make_path(maze, rows, cols);
	} while(!valid_path);
		
	return maze;
}
/*
 * Input: 2 dimensional array representing the maze, number of rows and columns of the maze
 * Function: Generate a maze with walls and the start and exit marked
 */
static void generate_maze(char** maze, int rows, int cols){
	int i, j;
	/*Randomly set start and exit points*/
	int start = 1 + rand() % (cols-2);
	int exit = 1 + rand() % (cols-2);
	for(i=0; i<rows; i++){
		for(j=0;j<cols;j++){ 
			/* place start, exit, and walls */
			if(i==0 && j==start) *(*(maze+i)+j)='S';
			else if (i==rows-1 && j==exit) *(*(maze+i)+j)='E';
			else *(*(maze+i)+j)='#';
		}
	}
}

/*
 * Input: Generated maze, number of rows and columns of the maze
 * Return: 1 if a path was successfully created, 0 otherwise
 * Function: Create a valid path through the maze
 */
static int make_path(char** maze, int rows, int cols){
	int i, j;
	int current_row, current_col;
	int next_row, next_col;
	int direction;	
	/*Max attempts to create path*/
	int fail_attempts = MAX_PATH_FAILURES;
	/*Limit open spaces to 25%*/
	float max_open_spaces = 0.25*rows*cols;
	char* start_point;
	/*Find starting point*/
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			if(*(*(maze+i)+j)=='S'){
				start_point=*(maze+i+1)+j;
				current_row=i+1;
				current_col=j;
			}
		}
	}
	*start_point='.';
	max_open_spaces--;
	/*Loop that does a random walk around the maze to create a path*/
	while(1){
		next_row=current_row;
		next_col=current_col;
		/*Pick a random direction 1 is up, 2 is down, 3 is right, 4 is left*/
		direction= 1 + rand() % 4;
		/*Next cell based on direction*/
		if(direction==1 && current_row>1){
			next_row--;
		} else if (direction==2 && current_row<rows-2){
			next_row++;
		} else if (direction==3 && current_col<cols-2){
			next_col++;
		} else if (direction==4 && current_col>1){
			next_col--;
		}
		start_point = *(maze+next_row)+next_col;
		/*Check if exit is found*/
		if(*(*(maze+next_row+1)+next_col) == 'E') {
			*start_point='.';
			return 1;
			/*If next cell is a wall, set it to a path*/
		} else if(*start_point=='#'){
			*start_point='.';
			current_col=next_col;
			current_row=next_row;
			max_open_spaces--;
		} else if(*start_point=='.'){
			fail_attempts--;
		}
		/*If more than 25% of the maze is open or if the path fails to progess too many times, exit */
		if(max_open_spaces<1 || fail_attempts==0){
			return 0;
		}
	}
	return 0;
}	
