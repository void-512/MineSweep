#include "box.h"

const bool isMine(const Box *b) {
    assert(b);
    return b -> mine;
}

void setMine(Box *b, bool m) {
    assert(b);
    b -> mine = m;
}

const Flag getShowState(const Box *b) {
    assert(b);
    return b -> flag;
}

void setShowState(Box *b, Flag f) {
    assert(b);
    b -> flag = f;
}

const short getMineAround(const Box *b) {
    assert(b);
    return b -> mineAround;
}

void setMineAround(Box *b, short n) {
    assert(b);
    b -> mineAround = n;
}