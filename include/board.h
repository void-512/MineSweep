#ifndef __BOARD_H__
#define __BOARD_H__

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "box.h"

typedef struct {
    Box **data;
    int row;
    int column;
    int numMines;
    int numMarked;
    int numDiscovered;
} Board;

// init(row, col): initialize a board with randomly distributed mines
Board *init(int row, int column, int numMines);

// freeBoard(board): free the board
void freeBoard(Board *board);

// getRow(board): returns number of rows in board
int getRow(const Board *board);

// getCol(board): returns number of rows in board
int getCol(const Board *board);

// getSingle(board, r, c): returns address of a single box in board at [i, j]
Box *getSingle(const Board *board, int r, int c);

// getNumMines(board): returns number of mines
int getNumMines(const Board *board);

// getNumMines(board): returns number of boards marked as mine
int getNumMarked(const Board *board);

// getNumMines(board): set number of boards marked as mine to n
void setNumMarked(Board *board, int n);

// getDiscoveredMines(board): returns numer of mines been discovered
int getDiscoveredMines(const Board *board);

// setDiscoveredMines(board): change numer of mines been discovered
void setDiscoveredMines(Board *board, int n);

#endif