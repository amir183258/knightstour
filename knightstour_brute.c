#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARDSIZE 8

// Main board
int board[BOARDSIZE][BOARDSIZE] = {0};

// All possible moves
int horizontal[] = {2, 1, -1, -2, -2, -1, 1, 2};
int vertical[] = {-1, -2, -2, -1, 1, 2, 2, 1};

void move(int moveNumber, int *x, int *y);
int validMove(int moveNumber, int x, int y);
void printBoard(int cols, int board[][cols]);
int arraySum(int size, const int arr[]);
void makeBoardZero(int rows, int cols, int board[rows][cols]);

int main() {
	int currentRow = 0;
	int currentColumn = 0;
	
	board[currentRow][currentColumn] = 1;

	srand(time(NULL));
	
	size_t i;
	int bestSolution = 0;
	int bestBoard[8][8] = {0};
	for (i = 0; bestSolution != 64; ++i) {
		int totalMoves = 64;
		size_t moveCount, moveNumber;
		int choosenMove = 0;
		int validMoves[8] = {0};
		int performedMoves = 1;
		currentRow = 0;
		currentColumn = 0;
		makeBoardZero(8, 8, board);
		board[currentRow][currentColumn] = 1;
		for (moveCount = 2; moveCount <= totalMoves && choosenMove != 10; ++moveCount) {
			for (moveNumber = 0; moveNumber < 8; ++moveNumber)
				if (validMove(moveNumber, currentRow, currentColumn))
					validMoves[moveNumber] = 1;
				else
					validMoves[moveNumber] = 0;

			choosenMove = 10;
			while (arraySum(8, validMoves) && choosenMove == 10)
				for (moveNumber = 0; moveNumber < 8; ++moveNumber)
					if (validMoves[moveNumber]) {
						int randomChooser = rand() % 100;
						if (randomChooser < 50)
							choosenMove = moveNumber;
					}

			if (choosenMove != 10) {
				move(choosenMove, &currentRow, &currentColumn);
				++performedMoves;
				board[currentRow][currentColumn] = performedMoves;
			}
		}
		if (performedMoves > bestSolution) {
			bestSolution = performedMoves;
			size_t r, c;
			for (r = 0; r < 8; ++r)
				for (c = 0; c < 8; ++c)
					bestBoard[r][c] = board[r][c];
		}
	}

	//printf("\nTotal Moves: %d\n",  performedMoves);
	printBoard(BOARDSIZE, bestBoard);
	printf("\nBest Soltuion: %d\n", bestSolution);


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

int arraySum(int size, const int arr[]) {
	size_t i;
	int sum = 0;
	for (i = 0; i < size; ++i)
		sum += arr[i];
	return sum;
}

void makeBoardZero(int rows, int cols, int board[rows][cols]) {
	size_t i, j;
	for (i = 0; i < rows; ++i)
		for (j = 0; j < cols; ++j)
			board[i][j] = 0;
}
