#include "Util.h"

static char* GetPostfix(char* input) {
    Stack* operators = NewStack();
    Stack* operands = NewStack();

    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];
        if (c == '(') {
            operators->Push(operators, c);
        } else if (c == ')') {
            while (1) {
                char op = operators->Pop(operators);
                if (op == '(')
                    break;
                String* s2 = operands->Pop(operands);
                String* s1 = operands->Pop(operands);
                s1->AppendStr(s1, s2);
                DeleteString(s2);
                s1->AppendChar(s1, op);
                operands->Push(operands, s1);
            }
        } else if (c == '+' || c == '-') {
            while (!operators->IsEmpty(operators) && operators->Peek(operators) != '(') {
                char op = operators->Pop(operators);
                String* s2 = operands->Pop(operands);
                String* s1 = operands->Pop(operands);
                s1->AppendStr(s1, s2);
                DeleteString(s2);
                s1->AppendChar(s1, op);
                operands->Push(operands, s1);
            }
            operators->Push(operators, c);
        } else if (c == '*' || c == '/') {
            while (!operators->IsEmpty(operators) && operators->Peek(operators) != '('&& operators->Peek(operators) != '+'&& operators->Peek(operators) != '-') {
                char op = operators->Pop(operators);
                String* s2 = operands->Pop(operands);
                String* s1 = operands->Pop(operands);
                s1->AppendStr(s1, s2);
                DeleteString(s2);
                s1->AppendChar(s1, op);
                operands->Push(operands, s1);
            }
            operators->Push(operators, c);
        } else {
            operands->Push(operands, NewString2(c));
        }
    }

    while (!operators->IsEmpty(operators)) {
        char op = operators->Pop(operators);
        String* s2 = operands->Pop(operands);
        String* s1 = operands->Pop(operands);
        s1->AppendStr(s1, s2);
        DeleteString(s2);
        s1->AppendChar(s1, op);
        operands->Push(operands, s1);
    }

    String* s = operands->Pop(operands);
    char* ret = malloc(1 + strlen(s->_str));
    strcpy(ret, s->Get(s));
    DeleteString(s);

    DeleteStack(operators);
    DeleteStack(operands);
    return ret;
}

void _6_2_Postfix() {
    char* ret = GetPostfix("a+b");
    check(strcmp(ret, "ab+") == 0);
    free(ret);

    ret = GetPostfix("a+b*c");
    check(strcmp(ret, "abc*+") == 0);
    free(ret);

    ret = GetPostfix("a+b-c+d*e/f");
    check(strcmp(ret, "ab+c-de*f/+") == 0);
    free(ret);

    ret = GetPostfix("(a+b-c)");
    check(strcmp(ret, "ab+c-") == 0);
    free(ret);    

    ret = GetPostfix("(a+b)*c");
    check(strcmp(ret, "ab+c*") == 0);
    free(ret);    

    ret = GetPostfix("d/((a+b)*c)");
    check(strcmp(ret, "dab+c*/") == 0);
    free(ret);        

}