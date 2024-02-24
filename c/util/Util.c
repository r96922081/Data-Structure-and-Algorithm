#include "Util.h"

void check(int ret)
{
    if (ret == 0) {
        assert(0);
    }
}


Point* NewPoint(int x, int y) {
    Point* p = calloc(1, sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

Pair* NewPair(void* first, void* second) {
    Pair* p = calloc(1, sizeof(Pair));
    p->first = first;
    p->second = second;
    return p;    
}