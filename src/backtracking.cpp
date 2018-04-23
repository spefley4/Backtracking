#include <iostream>
#include <chrono>
#include <thread>

/**
 * Following functions from: https://github.com/irawoodring/263/blob/master/backtracking/sample_code/backtracking.cpp
**/

// Prints the board out in a string format with its current values.
void printBoard(int board[9][9]) {
	printf("==============================================\n");
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			printf("%d\t", board[row][col]);
		}
		printf("\n");
	}
}

// Cycles through each space in the board, if the spot has yet to be assigned a value, row and col are updated and the function returns false. 
bool findSpot(int board[9][9], int & row, int & col) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			if (board[r][c] == 0) {
				row = r;
				col = c;
				return false;
			}
		}
	}
	return true;
}

/**
 * Following functions from: https://stackoverflow.com/questions/19022739/sudoku-solver-in-c
**/

// Returns whether any assigned entry in the specified row matches the given number.
bool UsedInRow(int board[9][9], int row, int val) {
	for (int col = 0; col < 9; col++) {
		if (board[row][col] == val) {
        		return true;
		}
	}

	return false;
}

// Returns whether any assigned entry in the specified column matches the given number.
bool UsedInCol(int board[9][9], int col, int val) {
	for (int row = 0; row < 9; row++) {
		if (board[row][col] == val) {
			return true;
		}
	}
	return false;
}

// Returns whether any assigned entry within the specified 3x3 box matches the given number.
bool UsedInBox(int board[9][9], int startRow, int startCol, int val) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row + startRow][col + startCol] == val) {
				return true;
			}
		}
	}
	return false;
}

// Returns whether it will be legal to assign num to the given location,
// based on whether val has not yet been used in the current row, column, and box.
bool isValid(int board[9][9], int row, int col, int val) {
	return !UsedInRow(board, row, val) && !UsedInCol(board, col, val) && 
		!UsedInBox(board, row - row % 3, col - col % 3, val);
}

// Function that intakes the board and recursively checks for a correct solution. 
bool solve(int board[9][9], int row, int col) {
	int r = row;
	int c = col;

	printf("Examining %d, %d.\n", r, c);
	printBoard(board);

	if (findSpot(board, r, c)) {
		return true;
	}

	for (int val = 1; val < 10; val++) {
		if(isValid(board, r, c, val)) {
			board[r][c] = val;

			if(solve(board, r, c)) {
				return true;
			}

			printf("Backtracking.\n");
			board[r][c] = 0;
		}
	
	}
	return false;
}

int main(int argc, char** argv){
	int board[9][9] = {{ 0, 3, 0, 0, 0, 0, 0, 2, 0 },
		{ 0, 9, 0, 0, 0, 0, 0, 8, 5 },
		{ 5, 0, 0, 0, 8, 0, 4, 0, 0 },
		{ 4, 0, 7, 2, 0, 6, 8, 9, 0 },
		{ 0, 1, 0, 8, 0, 9, 0, 4, 0 },
		{ 0, 8, 9, 5, 0, 1, 3, 0, 2 },
		{ 0, 0, 3, 0, 1, 0, 0, 0, 9 },
		{ 9, 4, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 7, 0, 0, 0, 0, 0, 3, 0 }
	};

	bool complete = solve(board, 0, 0);

	if (complete) {
		printf("Found a solution:\n\n");
	} else {
		printf("No solution found.");
	}
}																					
