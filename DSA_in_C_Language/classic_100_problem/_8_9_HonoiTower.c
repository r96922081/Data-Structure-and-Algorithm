#include "Util.h"
#include "Stack.h"

static Stack* s1;
static Stack* s2;
static Stack* s3;

char* name1 = "rod 1";
char* name2 = "rod 2";
char* name3 = "rod 3";

static char* GetDiscName(Stack* s) {
    if (s == s1) {
        return name1;
    } else if (s == s2) {
        return name2;
    } else {
        return name3;
    } 
}

static void MoveOneDisc(Stack* from, Stack* to) {
    int disc = from->Pop(from);

    if (!to->IsEmpty(to)) {
        int toTop = to->Peek(to);
        check(toTop > disc);
    }
    
    printf("Move disc %d from %s to %s\n", disc, GetDiscName(from), GetDiscName(to));
    to->Push(to, disc);
}

static void HonoiTower(Stack* src, Stack* temp, Stack* dest, int n) {
    if (n == 1) {
        MoveOneDisc(src, dest);
    } else {
        HonoiTower(src, dest, temp, n - 1);
        MoveOneDisc(src, dest);
        HonoiTower(temp, src, dest, n - 1);
    }
}

void _8_9_HonoiTower(int n) {
    s1 = NewStack();
    s2 = NewStack();
    s3 = NewStack();

    for (int i = n; i > 0; i--) {
        s1->Push(s1, i);
    }

    s1->PrintFromBottomToTop(s1);
    s2->PrintFromBottomToTop(s2);
    s3->PrintFromBottomToTop(s3);
    HonoiTower(s1, s2, s3, n);
    s1->PrintFromBottomToTop(s1);
    s2->PrintFromBottomToTop(s2);
    s3->PrintFromBottomToTop(s3);    

    DeleteStack(s3);
    DeleteStack(s2);
    DeleteStack(s1);
}