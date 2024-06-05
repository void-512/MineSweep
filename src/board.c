#include "board.h"
#include "box.h"
#include <time.h>

// generateMines(board, numMines): generate mines randomly with numMines in board
static void generateMines(Board *board, int numMines) {
    int row = getRow(board);
    int col = getCol(board);
    int **locations = calloc(2, sizeof(int*));
    locations[0] = calloc(numMines, sizeof(int));
    locations[1] = calloc(numMines, sizeof(int));

    srand((unsigned)time(NULL));

    for (int i = 0; i < numMines; i++) {
        bool dup = false;
        int r = rand() % row;
        int c = rand() % col;
        for (int j = 0; j < i; j++) {
            if (r == locations[0][j] && c == locations[1][j]) {
                dup = true;
                break;
            }
        }
        if (dup) {
            i--;
            continue;
        } else {
            locations[0][i] = r;
            locations[1][i] = c;
            setMine(getSingle(board, r, c), true);
        }
    }

    free(locations[0]);
    free(locations[1]);
    free(locations);
}

// updateMineAround(board): update the number of mines surrounded for each single box
static void updateMineAround(Board *board) {
    int row = getRow(board);
    int col = getCol(board);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Box *box = getSingle(board, i, j);
            // 4 corners
            if (i == 0 && j == 0) {
                setMineAround(box, isMine(getSingle(board, i + 1, j))
                                 + isMine(getSingle(board, i, j + 1))
                                 + isMine(getSingle(board, i + 1, j + 1)));
            } else if (i == 0 && j == col - 1) {
                setMineAround(box, isMine(getSingle(board, i + 1, j))
                                 + isMine(getSingle(board, i, j - 1))
                                 + isMine(getSingle(board, i + 1, j - 1)));
            } else if (i == row - 1 && j == 0) {
                setMineAround(box, isMine(getSingle(board, i - 1, j))
                                 + isMine(getSingle(board, i, j + 1))
                                 + isMine(getSingle(board, i - 1, j + 1)));
            } else if (i == row - 1 && j == col - 1) {
                setMineAround(box, isMine(getSingle(board, i - 1, j))
                                 + isMine(getSingle(board, i, j - 1))
                                 + isMine(getSingle(board, i - 1, j - 1)));
            } 
            // 4 edges
            else if (i == 0) {
                setMineAround(box, isMine(getSingle(board, i, j - 1))
                                 + isMine(getSingle(board, i + 1, j - 1))
                                 + isMine(getSingle(board, i + 1, j))
                                 + isMine(getSingle(board, i + 1, j + 1))
                                 + isMine(getSingle(board, i, j + 1)));
            } else if (i == row - 1) {
                setMineAround(box, isMine(getSingle(board, i, j - 1))
                                 + isMine(getSingle(board, i - 1, j - 1))
                                 + isMine(getSingle(board, i - 1, j))
                                 + isMine(getSingle(board, i - 1, j + 1))
                                 + isMine(getSingle(board, i, j + 1)));
            } else if (j == 0) {
                setMineAround(box, isMine(getSingle(board, i - 1, j))
                                 + isMine(getSingle(board, i - 1, j + 1))
                                 + isMine(getSingle(board, i, j + 1))
                                 + isMine(getSingle(board, i + 1, j + 1))
                                 + isMine(getSingle(board, i + 1, j)));
            } else if (j == col - 1) {
                setMineAround(box, isMine(getSingle(board, i - 1, j))
                                 + isMine(getSingle(board, i - 1, j - 1))
                                 + isMine(getSingle(board, i, j - 1))
                                 + isMine(getSingle(board, i + 1, j - 1))
                                 + isMine(getSingle(board, i + 1, j)));
            } 
            // others
            else {
                setMineAround(box, isMine(getSingle(board, i - 1, j - 1))
                                 + isMine(getSingle(board, i - 1, j))
                                 + isMine(getSingle(board, i - 1, j + 1))
                                 + isMine(getSingle(board, i, j - 1))
                                 + isMine(getSingle(board, i, j + 1))
                                 + isMine(getSingle(board, i + 1, j - 1))
                                 + isMine(getSingle(board, i + 1, j))
                                 + isMine(getSingle(board, i + 1, j + 1)));
            }
        }
    }
}

Board *init(int row, int col, int numMines) {
    Board *board = malloc(sizeof(Board));
    board -> row = row;
    board -> column = col;
    board -> data = (Box**)calloc(row, sizeof(Box*));
    board -> numMines = numMines;
    for (int i = 0; i < row; i++) {
        board -> data[i] = (Box*)calloc(col, sizeof(Box));
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            setShowState(getSingle(board, i, j), NONE);
        }
    }
    generateMines(board, numMines);
    updateMineAround(board);
    return board;
}

void freeBoard(Board *board) {
    for (int i = 0; i < getRow(board); i++) {
        free(board -> data[i]);
    }
    free(board -> data);
    free(board);
}

int getRow(const Board *board) {
    assert(board);
    return board -> row;
}

int getCol(const Board *board) {
    assert(board);
    return board -> column;
}

Box *getSingle(const Board *board, int r, int c) {
    assert(board);
    assert(r < getRow(board));
    assert(c < getCol(board));
    return &board -> data[r][c];
}

int getNumMines(const Board *board) {
    assert(board);
    return board -> numMines;
}

int getNumMarked(const Board *board) {
    assert(board);
    return board -> numMarked;
}

void setNumMarked(Board *board, int n) {
    assert(board);
    board -> numMarked = n;
}

int getDiscoveredMines(const Board *board) {
    assert(board);
    return board -> numDiscovered;
}

void setDiscoveredMines(Board *board, int n) {
    assert(board);
    board -> numDiscovered = n;
}