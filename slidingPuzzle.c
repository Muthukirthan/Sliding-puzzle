#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

void printSquareBoard(int size, int square[size][size]){
	system("cls");
	printf("-- SLIDING PUZZLE --\n");
	for(int i=0; i<size; i++){
		for(int j=0; j<size; printf(" -----"),j++);
		printf("\n|  ");
		for(int j=0; j<size; j++)
			if(square[i][j] == 0)
				printf("-  |  ");
			else if(square[i][j] < 10)
				printf("%d  |  ",square[i][j]);
			else
				printf("%d |  ",square[i][j]);
		printf("\n");
	}
	for(int j=0; j<size; printf(" -----"),j++);
	printf("\n");
	printf("Pres q to quit !\n\n");
}

void swap(int size, int square[size][size], int row1, int col1, int row2, int col2){		// Swaps the square values in two indices
	int temp = square[row1][col1];
	square[row1][col1] = square[row2][col2];
	square[row2][col2] = temp;
}

void up(int size, int square[size][size], int *row, int *col){			// Function for up operation
	if(*row > 0)
		swap(size, square, *row, *col, (*row)--, *col);
	else
		printf("\a");
}

void down(int size, int square[size][size], int *row, int *col){			// Function for up operation
	if(*row < size-1)
		swap(size, square, *row, *col, (*row)++, *col);
	else
		printf("\a");
}

void left(int size, int square[size][size], int *row, int *col){			// Function for up operation
	if(*col > 0)
		swap(size, square, *row, *col, *row, (*col)--);
	else
		printf("\a");
}

void right(int size, int square[size][size], int *row, int *col){			// Function for up operation
	if(*col < size-1)
		swap(size, square, *row, *col, *row, (*col)++);
	else
		printf("\a");
}

int won(int size, int square[size][size]){	// This function checks if the square is same as expected
	int i,j,value;
	for(i=0, value=1; i<size; i++)
		for(j=0; j<size; j++)
			if(square[i][j] != value++)
				break;
	if(i == size && j == size-1)
		return 1;
	else
		return 0;
}

void startGame(int size, int square[size][size], int zero_row, int zero_col){
//	Loop till user won the game or chooses to quit
	while(1){
		printSquareBoard(size, square);
		
//		Check if won
		if(won(size, square)){
			printf("\n\t\tYou Won !");
			break;
		}
		
//		When arrow keys are entered to getch(), two values are sent by the compiler.
//		One value is -32 and the other is 72, 80, 75 or 77 based on the arrow key
//		So, enter input till q or arrow key is pressed.
//		
//		if q is entered, game quits.
//		else(arrow key is pressed), second value is sent to second getch(), which is used in switch
		
		char c = getch();
		while(c != 'q' && c != -32){
			printf("Use arrow keys to play the game!\n");
			c = getch();
		}
		//		Check if user wants to quit the game
		if(c == 'q')
			break;
		
		//		Check which arrow key is pressed
		switch(getch()) {
	        case 72:	// Up arrow
	            up(size, square, &zero_row, &zero_col); 		// As c does not support returning multiple values, index(row and col) are passed by reference
	            break;
	            
	        case 80:	// Down arrow
	            down(size, square, &zero_row, &zero_col);		// As c does not support returning multiple values, index(row and col) are passed by reference
				break;
				
	        case 75:	// Left arrow
	            left(size, square, &zero_row, &zero_col);		// As c does not support returning multiple values, index(row and col) are passed by reference
				break;
				
	        case 77:	// Right arrow
	            right(size, square, &zero_row, &zero_col);		// As c does not support returning multiple values, index(row and col) are passed by reference
				break;
				
			default:
				printf("Use arrow keys to play the game!\n");
	    }
	}
	
}

int main(){
//	int square[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{0,13,14,15}};
//	int zero_row = 3, zero_col = 0;
	
	int size, game_level;
	printf("\t\tDifficulty level:\n");
	printf("\t\t 1.Easy (3x3)\n\n");
	printf("\t\t 2.Medium (4x4)\n\n");
	printf("\t\t 3.Hard (5x5)\n\n");
	printf("\nplease enter the difficulty level of game: ");
	scanf("%d",&game_level);
	while(game_level < 0 || game_level > 3){
		printf("\nplease enter a proper choice: ");
		scanf("%d",&game_level);
	}
	switch(game_level){
		case 1:
			size = 3;
			break;
		case 2:
			size = 4;
			break;
		case 3:
			size = 5;
			break;
	}
	int square[size][size];

	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			square[i][j] = -1;
	int zero_row = 0, zero_col = 0;
	
//	Generate random index for square and assign values from expected array.

// rand() always generates randum numbers in a series with default srand(1).
// if you want to generate different series of random numbers each time, run srand(time(0))
	srand(time(0));
	for(int i=0, value=0; i<size; i++)
		for(int j=0; j<size; j++){
			int row = rand() % size;
			int col = rand() % size;
			while(square[row][col] != -1){
				row = rand() % size;
				col = rand() % size;
			}
			if(value == 0){
				zero_row = row;
				zero_col = col;
			}
			square[row][col] = value++;
		}
//		Game starts with randomly shuffled square
	startGame(size, square, zero_row, zero_col);
	return 0;
}
