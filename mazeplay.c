/* mazeplay.c
 * 
 * This file allows a user to explore a maze.
 *
 * CST8234 Assignment 1: Maze Runner
 * Student name: Budry Ahmed
 * Student number: 040801692
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

/*
 * Input: 2 dimensional array representing the maze, the rows and coloumns of the maze
 * Function: Allow movement around the maze, tracking position and number of moves
 */
void maze_play(char** maze, int rows, int cols){
	char option;
	int i, j;
	int number_of_moves = 0;
	int current_row, current_col;
	int next_row, next_col;
	char* play_point;
	char next_char;
	/*Find starting point*/
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			if(*(*(maze+i)+j)=='S'){
				play_point=*(maze+i)+j;
				current_row=i;
				current_col=j;
			}
		}
	}
	/*Gameplay loop*/
	while(1){
		print_maze(maze, rows, cols);
		next_row=current_row;
		next_col=current_col;
		printf("Move (W/A/S/D): ");
		scanf(" %c", &option);
		next_char=getchar();
		if(next_char!='\n' && next_char!=EOF) {
			printf("Invalid input\n\n");
			clearinputbuffer();
			continue;
		}
		/*Exit the game*/
		if(option=='Q' || option=='q'){
			printf("Goodbye\n");
			destroy_maze(maze, rows);
			exit(0);
		}
		/*Next position based on user input*/
		/*Go up*/
		if(option=='W' || option =='w'){
			if(current_row==0){
				printf("You walked into a wall!\n\n");
				continue;
			} else {
				next_row--;
			}
		/*Go left*/
		} else if (option=='A' || option =='a'){
			if(current_col==0){
				printf("You walked into a wall!\n\n");
				continue;
			} else {
				next_col--;
			}
		/*Go down*/
		} else if(option == 'S' || option =='s'){
			if(current_row==rows-1){
				printf("You walked into a wall!\n\n");
				continue;
			} else {
				next_row++;
			}
		/*Go right*/
		} else if(option == 'D' || option =='d'){
			if(current_col==cols-1){
				printf("You walked into a wall!\n\n");
				continue;
			} else {
				next_col++;
			}
		} else {
			printf("Invalid input\n\n");
			continue;
		}
		/*Update position*/
		play_point = *(maze+next_row)+next_col;
		if(*play_point=='.' || *play_point=='*'){
			*(*(maze+current_row)+current_col) = '*';
			*play_point = 'S';
			current_col=next_col;
			current_row=next_row;
			number_of_moves++;
			/*Exit found*/
			if(*(*(maze+next_row+1)+next_col) == 'E'){
				print_maze(maze, rows, cols);
				printf("Congratulations! You reached the exit in %d moves.\n",number_of_moves);
				break;
			}
			/*Wall collision*/
		} else if (*play_point=='#'){
			printf("You walked into a wall!\n\n");
				continue;
		}
	}
}

