#ifndef STRING_H
#define STRING_H

#include "Util.h"

typedef struct String String;

typedef struct String {
    char* (*Get)(String*);
    void (*AppendCharStr)(String*, char*);
    void (*AppendChar)(String*, char);
    void (*AppendStr)(String*, String*);
    char* _str;
} String;

String* NewString(char* s);
String* NewString2(char s2);
void DeleteString(String* s);

#endif