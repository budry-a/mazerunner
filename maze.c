/* maze.c
 * 
 * This program generates a maze and allows a user to explore it.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mazegen.h"
#include "mazeplay.h"
#include "utility.h"

/*
 * Entry point for the game, controls the gameplay loop
 */
int main(){
	char** maze = NULL;
	int rows;
	int cols;
	char option;
	char next_char;
	/*Seed the random number generator*/
	srand(time(NULL));
	printf("Welcome to Maze Runner!\n\n");
	while(1){
		/*Generates the random dimensions for the maze*/
		cols = 10 + rand() % 11;
		rows = 10 + rand() % 11;
		/*Create the maze*/
		maze = create_maze(rows, cols);
		/*Exit if maze creation fails*/
		if(maze==NULL){
			printf("unable to generate maze\n");
			break; 
		}
		/*Gameplay begins*/
		printf("Maze Generated. Reach the exit (E).\n");
		printf("Use W/A/S/D to move. Press Q to quit.\n\n");
		maze_play(maze, rows, cols);
		/*Prompt to play again*/
		printf("Would you like to play again? (Y/N): ");
		scanf(" %c",&option);
		next_char=getchar();
		if(next_char!='\n' && next_char!=EOF) {
			printf("Invalid input\n\n");
			clearinputbuffer();
			option='n';
		}
		/*Free memory and play again*/
		if(option=='y' || option=='Y'){
			destroy_maze(maze, rows);
			continue;
		} else {
			/*Free memory and exit*/
			printf("Goodbye\n");
			destroy_maze(maze, rows);
			exit(0);
		}
	}
	return 1;
}


