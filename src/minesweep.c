#include "board.h"
#include "box.h"
#include "interaction.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int DEFAULTROW = 5;
const int DEFAULTCOL = 10;
const int DEFAULTMINE = 5;

static void help() {
    puts("Argument Format: ./MineSweep [row] [col] [mine]");
    puts("Default Values: 5 10 5");
    puts("Requirement: [mine] < [row] * [col]");
}

static void argProcessor(int argc, char **argv, unsigned int *row, unsigned int *col, unsigned int *mine) {
    if (argc == 2 && !strcmp(argv[1], "-h")) {
        help();
        exit(0);
    }

    switch (argc) {
        case 2:
            *row = atoi(argv[1]);
            break;
        case 3:
            *row = atoi(argv[1]);
            *col = atoi(argv[2]);
            break;
        case 4:
            *row = atoi(argv[1]);
            *col = atoi(argv[2]);
            *mine = atoi(argv[3]);
            break;
        default:
            return;
    }

    if (*row == 0 ||
        *col == 0 ||
        *mine == 0 ||
        (*mine > *row * *col)) {
        help();
        puts("Wrong Input");
        exit(0);
    }
}

int main(int argc, char **argv) {
    unsigned int row = DEFAULTROW;
    unsigned int col = DEFAULTCOL;
    unsigned int mine = DEFAULTMINE;
    
    argProcessor(argc, argv, &row, &col, &mine);
    
    Board *gameBoard = init(row, col, mine);
    while (true) {
        display(gameBoard, false);
        EndStatus result = updateState(gameBoard, getInput(gameBoard), false);
        if (result != NOTEND) {
            display(gameBoard, true);
            gameBoard = endOption(result, gameBoard);
        }
    }

    return 0;
}