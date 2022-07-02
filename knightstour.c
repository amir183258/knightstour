#include <stdio.h>

#define BOARDSIZE 8

// Main board
int board[BOARDSIZE][BOARDSIZE] = {0};

// All possible moves
int horizontal[] = {2, 1, -1, -2, -2, -1, 1, 2};
int vertical[] = {-1, -2, -2, -1, 1, 2, 2, 1};

void move(int moveNumber, int *x, int *y);
int validMove(int moveNumber, int x, int y);
void printBoard(int cols, int board[][cols]);

int main() {
	int currentRow = 0;
	int currentColumn = 0;
	board[currentRow][currentColumn] = 1; // This is the first move.

	int accessibility[8][8] = {{2, 3, 4, 4, 4, 4, 3, 2},
		             	   {3, 4, 6, 6, 6, 6, 4, 3},
			           {4, 6, 8, 8, 8, 8, 6, 4},
			           {4, 6, 8, 8, 8, 8, 6, 4},
			           {4, 6, 8, 8, 8, 8, 6, 4},
			           {4, 6, 8, 8, 8, 8, 6, 4},
		                   {3, 4, 6, 6, 6, 6, 4, 3},
			           {2, 3, 4, 4, 4, 4, 3, 2}};

	int totalMoves = 64, knightMoves = 8;
	int minAccessibility; // Greater than max(accessibility) to compute min.
	int score, bestMove;
	int moveCounter = 1;
	size_t i, j;
	// i = 1 because we did a move in initial position.
	for (i = 1; i < totalMoves; ++i) {
		minAccessibility = 10;
		for (j = 0; j < knightMoves; ++j) 
			if (validMove(j, currentRow, currentColumn)) {
				--accessibility[currentRow + vertical[j]][currentColumn + horizontal[j]];
				score = accessibility[currentRow + vertical[j]][currentColumn + horizontal[j]];
				if (score < minAccessibility) {
					bestMove = j;
					minAccessibility = score;
				}
			}
		move(bestMove, &currentRow, &currentColumn);
		++moveCounter;
		board[currentRow][currentColumn] = moveCounter;
	}
	printBoard(BOARDSIZE, board);

	return 0;
}

void move(int moveNumber, int *x, int *y) {
	if (validMove(moveNumber, *x, *y)) {
		*x += vertical[moveNumber];
		*y += horizontal[moveNumber];
	}
}

int validMove(int moveNumber, int x, int y) {
	x += vertical[moveNumber];
	y += horizontal[moveNumber];
	if (board[x][y] == 0 && (x >= 0 && x < BOARDSIZE) && (y >= 0 && y < BOARDSIZE))
		return 1;
	else
		return 0;
}

void printBoard(int cols, int board[][cols]) {
	size_t i;
	size_t j;
	for (i = 0; i < BOARDSIZE; ++i) {
		for (j = 0; j < BOARDSIZE; ++j)
			printf("%3d", board[i][j]);
		puts("");
	}
}
