#include "Util.h"

static char* FindMismatch(char* input) {
    char* ret = calloc(1, strlen(input) + 1);
    memset(ret, ' ', strlen(input));

    Stack* s = NewStack();

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '(') {
            s->Push(s, i);
        } else {
            if (s->IsEmpty(s)) {
                ret[i] = '^';
            } else {
                s->Pop(s);
            }
        }
    }


    while (!s->IsEmpty(s)) {
        int pos = s->Pop(s);
        ret[pos] = '^';
    }

    DeleteStack(s);
    printf("%s\n%s\n", input, ret);
    return ret;
}

void _6_1_ParenthesesMatch() {
    char* ret = FindMismatch("()");
    check(strcmp(ret, "  ") == 0);
    free(ret);

    ret = FindMismatch("(()");
    check(strcmp(ret,  "^  ") == 0);
    free(ret);

    ret = FindMismatch("(())(");
    check(strcmp(ret,  "    ^") == 0);
    free(ret);

    ret = FindMismatch("(())()((");
    check( strcmp(ret, "      ^^") == 0);
    free(ret);    

    ret = FindMismatch(")(()");
    check( strcmp(ret, "^^  ") == 0);
    free(ret); 

    ret = FindMismatch("(()()");
    check( strcmp(ret, "^    ") == 0);
    free(ret);             
}