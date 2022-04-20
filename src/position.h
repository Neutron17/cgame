//
// Created by neutron17 on 2022.04.18..
//

#ifndef _NTR_POSITION_H_
#define _NTR_POSITION_H_

typedef struct {
    int y;
    int x;
} pos;

// Position arithmetic
pos pDiff(pos x, pos y);
int pSum (pos n);
unsigned pSumU(pos x);
#define pSame(x,y) (pSumU(pDiff(x,y)) == 0)

#endif //_NTR_POSITION_H_