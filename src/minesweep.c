#include "board.h"
#include "box.h"
#include "interaction.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    Board *newBoard = init(5, 10, 5);
    while (true) {
        display(newBoard, false);
        EndStatus result = updateState(newBoard, getInput(newBoard), false);
        if (result == LOSS) {
            display(newBoard, true);
            printf("You lost\n");
            break;
        }
        if (result == WIN) {
            display(newBoard, true);
            printf("You win\n");
            break;
        }
    }
    freeBoard(newBoard);
    return 0;
}