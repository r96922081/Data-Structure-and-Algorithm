#include "Util.h"

static char* GetPrefix(char* s) {

}

void _6_3_Prefix() {
    char* ret = GetPrefix("3+4");
    check(strcmp(ret, "+34") == 0);
    free(ret);

    ret = GetPrefix("3+4*5");
    check(strcmp(ret, "+3*45") == 0);
    free(ret);

    ret = GetPrefix("3+4+5+6");
    check(strcmp(ret, "+++3456") == 0);
    free(ret);  

    ret = GetPrefix("2*3+4*5/6-7");
    check(strcmp(ret, "-+*23/*4567") == 0);
    free(ret);  

    ret = GetPrefix("3*(4-(5+6))");
    check(strcmp(ret, "*3-4+56") == 0);
    free(ret);        

    ret = GetPrefix("2*(3+4)/(4+5)-6/(7+8)");
    check(strcmp(ret, "-/*2+34+45/6+78") == 0);
    free(ret);        
}