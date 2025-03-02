#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define PROBLEM 103

#define MAIN(x) main##x
#define EXPAND(str) MAIN(str)
#define MAIN_FUNC EXPAND(PROBLEM)

// extern int main183
extern int MAIN_FUNC();

void RunCode() {
    int original_stdin = _dup(0);
    int original_stdout = _dup(1);

    char input[256];
    char output[256];

    sprintf(input, "input_and_answer\\uva%d_input.txt", PROBLEM);
    sprintf(output, "output.txt");

    freopen(input, "r", stdin);
    freopen(output, "w", stdout);

    MAIN_FUNC();

    _dup2(original_stdin, 0);
    _dup2(original_stdout, 1);
}

void CompareResult() {
    char answer[256];
    char output[256];

    sprintf(answer, "input_and_answer\\uva%d_answer.txt", PROBLEM);
    sprintf(output, "output.txt");

    char cmd[1024];
    sprintf(cmd, "fc %s %s", answer, output);

    int ret = system(cmd);
    if (ret == 0)
        printf("Pass\n");
    else
        printf("Failed\n");
}

int main()
{
    RunCode();
    CompareResult();
}