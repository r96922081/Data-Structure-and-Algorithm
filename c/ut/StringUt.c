#include "Util.h"

void StringUt() {
    String* s = NewString("");
    DeleteString(s);

    s = NewString("123");
    DeleteString(s);  

    String* s1 = NewString("");
    String* s2 = NewString("bc");
    s1->AppendStr(s1, s2);
    check(strcmp(s1->Get(s1), "bc") == 0);
    DeleteString(s1);
    DeleteString(s2);

    s1 = NewString("ab");
    s2 = NewString("cd");
    s1->AppendStr(s1, s2);
    check(strcmp(s1->Get(s1), "abcd") == 0);
    DeleteString(s1);
    DeleteString(s2);

    s1 = NewString("ab");
    s1->AppendCharStr(s1, "");
    check(strcmp(s1->Get(s1), "ab") == 0);
    DeleteString(s1); 

    s1 = NewString("ab");
    s1->AppendCharStr(s1, "cde");
    check(strcmp(s1->Get(s1), "abcde") == 0);
    DeleteString(s1);     

    s1 = NewString("a");
    s1->AppendChar(s1, 'b');
    check(strcmp(s1->Get(s1), "ab") == 0);
    DeleteString(s1);       
}