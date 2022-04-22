#include "position.h"
#include <stdlib.h>

inline pos pDiff(pos x, pos y) {
    return (pos) { (x.y - y.y), (x.x - y.x) };
}
inline int pSum (pos n) { return abs(n.x) + abs(n.y); }
inline unsigned pSumU(pos n) {
    int x = pSum(n);
    if(x < 0)
        return (unsigned)-x;
    return (unsigned)x;
}