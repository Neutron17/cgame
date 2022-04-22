#ifndef _NTR_POSITION_H_
#define _NTR_POSITION_H_

typedef struct {
    int y;
    int x;
} pos;

// Position arithmetic
extern inline pos pDiff(pos x, pos y);
extern inline int pSum (pos n);
extern inline unsigned pSumU(pos x);
#define pSame(x,y) (pSumU(pDiff(x,y)) == 0)

#endif //_NTR_POSITION_H_