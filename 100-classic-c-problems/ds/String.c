#include "Util.h"

String* NewString(char* s);
String* NewString2(char s2);
void DeleteString(String* s);

static char* Get(String*);
static void AppendCharStr(String*, char*);
static void AppendChar(String*, char);
static void AppendStr(String*, String*);

static char* Get(String* s) {
    return s->_str;
}

static void AppendCharStr(String* s1, char* s2) {
    char* temp = malloc(strlen(s1->_str) + strlen(s2) + 1);
    strcpy(temp, s1->_str);
    free(s1->_str);
    strcat(temp, s2);
    s1->_str = temp;
}

static void AppendStr(String* s1, String* s2) {
    AppendCharStr(s1, s2->_str);
}

static void AppendChar(String* s1, char c) {
    char* temp = calloc(1, strlen(s1->_str) + 2);
    strcpy(temp, s1->_str);
    temp[strlen(s1->_str)] = c;
    free(s1->_str);
    s1->_str = temp;
}

String* NewString(char* s2) {
    String* s = calloc(1, sizeof(String));
    s->Get = Get;
    s->AppendCharStr = AppendCharStr;
    s->AppendChar = AppendChar;
    s->AppendStr = AppendStr;

    s->_str = malloc(strlen(s2) + 1);
    strcpy(s->_str, s2);

    return s;
}

String* NewString2(char s2) {
    String* s = calloc(1, sizeof(String));
    s->Get = Get;
    s->AppendCharStr = AppendCharStr;
    s->AppendChar = AppendChar;
    s->AppendStr = AppendStr;

    s->_str = calloc(0, 2);
    s->_str[0] = s2;

    return s;
}

void DeleteString(String* s) {
    free(s->_str);
    free(s);
}