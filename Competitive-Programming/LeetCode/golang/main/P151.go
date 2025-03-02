package main

import "fmt"

func main() {
    fmt.Println("P151")
}

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void check(bool b) {
    if (!b)
    {
        int a= 1;
        int b = 2;
        int c =a/b;
    }
}

void reverseWords(char *s) {
    // trim head
    int leadingSpace = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == ' ')
            leadingSpace++;
        else
            break;
    }
    s += leadingSpace;

    // trim tail
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (s[i] == ' ')
            s[i] = '\0';
        else
            break;
    }   

    // remove extra space between words 
    int extraSpace = 0;
    for (int i = 1; i < strlen(s); i++) {
        if (s[i] == ' ' && s[i - 1] == ' ')
            extraSpace++;
        else
        {
            s[i - extraSpace] = s[i];
        }
    }  

    s[strlen(s) - extraSpace] = '\0';

    // reverse entire string
    char temp;
    for (int i = 0; i < strlen(s) / 2; i++) {
        temp = s[i];
        s[i] = s[strlen(s) - 1 - i];
        s[strlen(s) - 1 - i] = temp;
    }

    int left = -1;
    int right = -1;

    // reverse each sub-string
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ') {
            right = i - 1;
        } else {
            if (left == -1)
                left = i;
        }
        if (i == (strlen(s) - 1))
            right = i;
        
        if (left != -1 && right != -1)
        {
            char temp;
            int len = right -left + 1;
            for (int i = 0; i < len/2; i++) {
                temp = s[left + i];
                s[left + i] = s[right - i];
                s[right - i] = temp;
            }            
            left = -1;
            right = -1;
        }
    }

    for (int i = 0; i <= strlen(s); i++)
    {
        s[i- leadingSpace] = s[i];
    }
}

char buffer[1000];

int main()
{
    strcpy(buffer, "  a b123   c4  d56  ");
    reverseWords(buffer);
    check(strcmp(buffer, "d56 c4 b123 a") == 0);

    strcpy(buffer, "abb");
    reverseWords(buffer);
    check(strcmp(buffer, "abb") == 0);    

    strcpy(buffer, "    ");
    reverseWords(buffer);
    check(strcmp(buffer, "") == 0);   

    strcpy(buffer, "");
    reverseWords(buffer);
    check(strcmp(buffer, "") == 0);      
}
