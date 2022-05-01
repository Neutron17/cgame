#include "position.h"
#include <stdlib.h>

pos pDiff(pos x, pos y) {
	return (pos) { (x.y - y.y), (x.x - y.x) };
}
int pSum (pos n) { return abs(n.x) + abs(n.y); }
unsigned pSumU(pos n) {
	int x = pSum(n);
	if(x < 0)
		return (unsigned)-x;
	return (unsigned)x;
}