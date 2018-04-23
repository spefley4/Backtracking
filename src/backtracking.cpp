#include <iostream>
#include <chrono>
#include <thread>

#define UNASSIGNED 0
#define N 9

/**
 * Following functions from: https://github.com/irawoodring/263/blob/master/backtracking/sample_code/backtracking.cpp
**/

void printBoard(int board[9][9]) {
	printf("==============================================\n");
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			printf("%d\t", board[row][col]);
		}
		printf("\n");
	}
}

bool findSpot(int board[9][9], int & row, int & col) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			if (board[r][c] == UNASSIGNED) {
				row = r;
				col = c;
				return false;
			}
		}
	}
}

/**
 * Following functions from: https://stackoverflow.com/questions/19022739/sudoku-solver-in-c
**/

// Returns whether any assigned entry in the specified row matches the given number.
bool UsedInRow(int grid[N][N], int row, int val) {
	for (int col = 0; col < N; col++) {
		if (grid[row][col] == val) {
        		return true;
		}
	}

	return false;
}

// Returns whether any assigned entry in the specified column matches the given number.
bool UsedInCol(int grid[N][N], int col, int val) {
	for (int row = 0; row < N; row++) {
		if (grid[row][col] == val) {
			return true;
		}
	}
	return false;
}

// Returns whether any assigned entry within the specified 3x3 box matches the given number.
bool UsedInBox(int grid[N][N], int startRow, int startCol, int val) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == val) {
				return true;
			}
		}
	}
	return false;
}

// Returns whether it will be legal to assign num to the given location.
bool isValid(int grid[N][N], int row, int col, int num) {
	return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && 
		!UsedInBox(grid, row - row % 3, col - col % 3, num);
}

bool solve(int board[9][9], int x, int y) {
	int row = x;
	int col = y;

	printf("Examining %d, %d.\n", row, col);
	printBoard(board);

	if (findSpot(board, row, col)) {
		return true;
	}

	for (int val = 1; val < 10; val++) {
		if(isValid(board, row, col, val)) {
			board[row][col] = val;

			if(solve(board, row, col)) {
				return true;
			}

			printf("Backtracking.\n");
			board[row][col] = UNASSIGNED;
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
