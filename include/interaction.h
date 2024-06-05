#ifndef __INTERACTION_H__
#define __INTERACTION_H__

#include "board.h"
#include "box.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int r;
    int c;
    Flag f;
} Command;

typedef enum {WIN, LOSS, NOTEND} EndStatus;

// display(board, answer): display the board if answer is false and display real mines if answer is true
void display(const Board *board, bool answer);

// getInput(board): get input commands from stdin
Command getInput(const Board *board);

// updateState(board, input, updateRecursion): update the show status of board
EndStatus updateState(Board *board, Command input, bool updateRecursion);

#endif