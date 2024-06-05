#ifndef __BOX_H__
#define __BOX_H__

#include <assert.h>
#include <stdbool.h>

#define NUMFLAGS 4

typedef enum {UNCOVER, MINE, QUESTION, NONE} Flag;

typedef struct {
    bool mine;
    Flag flag;
    short mineAround;
} Box;

// isMine(b): returns bool indicating whether b is mine
const bool isMine(const Box *b);

// setMine(b, m): set b's feature of mine to m
void setMine(Box *b, bool m);

// getShowState(b): returns Flag indicating b's status when showed
const Flag getShowState(const Box *b);

// setShowState(b, f): set b's status of showing to f
void setShowState(Box *b, Flag f);

// getMineAround(b): get the number of mines around b
const short getMineAround(const Box *b);

// setMineAround(b, n): set the number of of mines around b to n
void setMineAround(Box *b, short n);

#endif