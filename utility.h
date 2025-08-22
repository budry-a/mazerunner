#ifndef UTILITY_H
#define UTILITY_H

/*
 * Input: Fully generated maze, the rows and coloumns of the maze
 * Function: Display the maze 
 */
void print_maze(char** maze, int rows, int cols);

/*
 * Input: the maze and the number of rows
 * Function: free memory allocated for the maze
 */
void destroy_maze(char** maze, int rows);

/*
 * Function: Clear standard input buffer
 */
void clearinputbuffer();

#endif