//
// Created by neutron17 on 2022.04.16..
//

#ifndef _NTR_BOARD_H_
#define _NTR_BOARD_H_

#define B_WID 6
#define B_HEI 5
char board[B_HEI][B_WID] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
};
#define PL_ICON 'X'

typedef struct {
    unsigned y;
    unsigned x;
} pos;
enum Movement {
    QUIT, NONE,
    UP, DOWN, LEFT, RIGHT
};

#endif //_NTR_BOARD_H_
