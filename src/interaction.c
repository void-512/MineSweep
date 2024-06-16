#include "interaction.h"
#include <assert.h>

static void displayHelp(const Board *board) {
    puts("Commands");
    printf("[%d] to checkout\n[%d] to mark as mine\n[%d] to mark as suspected\n[%d] to unmark\n", UNCOVER, MINE, QUESTION, NONE);
    printf("Number of Mines: %d\n", getNumMines(board));
    printf("Remaining Flags: %d\n", getNumMines(board) - getNumMarked(board));
}

void display(const Board *board, bool answer) {
    const int row = getRow(board);
    const int col = getCol(board);
    printf("%5s", "# |");
    for (int i = 0; i < col; i++) {
        printf("%3d", i);
    }
    puts("");
    for (int i = 0; i < col + 2; i++) {
        printf("---");
    }
    puts("");
    for (int i = 0; i < row; i++) {
        printf("%3d %c", i, '|');
        for (int j = 0; j < col; j++) {
            const Box *current = getSingle(board, i, j);
            if (!answer) {
                Flag flag = getShowState(current);
                if (flag == MINE) {
                    printf("%3c", 'X');
                } else if (flag == QUESTION) {
                    printf("%3c", '?');
                } else if (flag == UNCOVER) {
                    printf("%3d", getMineAround(current));
                } else {
                    printf("%3c", '*');
                }
            } else {
                if (isMine(current)) {
                    printf("%3c", 'X');
                } else {
                    printf("%3c", 'O');
                }
            }
        }
        puts("");
    }
    displayHelp(board);
    puts("");
}

Command getInput(const Board *board) {
    assert(board);
    Command input = {0, 0, 0};
    printf("[row] [col] [cmd]: ");
    int flagTemp = 0;
    int result = scanf("%d", &input.r) + scanf("%d", &input.c) + scanf("%d", &flagTemp);
    input.f = flagTemp;
    getchar();
    if (result != 3 || input.r > getRow(board) || input.c > getCol(board) || input.f < 0 || input.f > NUMFLAGS - 1) {
        puts("Wrong Input");
        display(board, false);
        return getInput(board);
    } else {
        return input;
    }
}

EndStatus updateState(Board *board, Command input, bool updateRecursion) {
    assert(board);
    int row = input.r;
    int col = input.c;
    int cmd = input.f;
    Box *current = getSingle(board, row, col);
    if (getShowState(current) == UNCOVER) {
        return NOTEND;
    } else if (cmd == NONE) {
        if (getShowState(current) == MINE) {
            if (isMine(current)){
                setDiscoveredMines(board, getDiscoveredMines(board) - 1);
            }
            setNumMarked(board, getNumMarked(board) - 1);
        }
        setShowState(current, cmd);
    } else if (cmd == MINE) {
        if (getShowState(current) != MINE) {
            setShowState(current, cmd);
            setNumMarked(board, getNumMarked(board) + 1);
            if (isMine(current)) {
                setDiscoveredMines(board, getDiscoveredMines(board) + 1);
            }
            if (getDiscoveredMines(board) == getNumMines(board)) {
                return WIN;
            }
        }
    } else if (cmd == QUESTION) {
        if (getShowState(current) == MINE) {
            if (isMine(current)){
                setDiscoveredMines(board, getDiscoveredMines(board) - 1);
            }
            setNumMarked(board, getNumMarked(board) - 1);
        }
        setShowState(current, cmd);
    } else if (cmd == UNCOVER) {
        if (getShowState(current) == UNCOVER) {
            return NOTEND;
        } else if (isMine(current)) {
            if (!updateRecursion) {
                return LOSS;
            } else {
                return NOTEND;
            }
        } else if (getMineAround(current) != 0) {
            setShowState(current, UNCOVER);
        } else if (getMineAround(current) == 0) {
            setShowState(current, UNCOVER);
            if (row > 0) {
                Command newCmd = {row - 1, col, UNCOVER};
                updateState(board, newCmd, true);
            }
            if (row < getRow(board) - 1) {
                Command newCmd = {row + 1, col, UNCOVER};
                updateState(board, newCmd, true);
            }
            if (col > 0) {
                Command newCmd = {row, col - 1, UNCOVER};
                updateState(board, newCmd, true);
            }
            if (col < getCol(board) - 1) {
                Command newCmd = {row, col + 1, UNCOVER};
                updateState(board, newCmd, true);
            }
        }
    }
    return NOTEND;
}

Board *endOption(const EndStatus result, Board *board) {
    assert(board);
    Board *gameBoard = NULL;
    puts(result == WIN ? "You Win" : "You Lost");
    puts("Another game [c] or any other keys to quit");
    if (getchar() == 'c') {
        gameBoard = init(getRow(board), getCol(board), getNumMines(board));
        freeBoard(board);
    } else {
        exit(0);
    }
    return gameBoard;
}