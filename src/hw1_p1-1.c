#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CAPACITY 100

char stack[CAPACITY]; // 暫放運算子的地方
int top = -1;
char cal[105], postfix[105];

bool IsFull()
{
    if (top == CAPACITY - 1)
        return true;
    return false;
}
bool IsEmpty()
{
    if (top <= -1)
        return true;
    return false;
}
void push(char c) // 運算完 top 指在正確的 top
{
    if (!IsFull())
    {
        top++;
        stack[top] = c;
    }
    else
        printf("Full");
}
char pop() // 運算完 top 指在正確的 top
{
    if (!IsEmpty())
    {
        top--;
        return stack[top + 1];
    }
    else
        return false;
}

int main()
{
    // infix to postfix
    // test1: (A+B)/C*D -> AB+C/D*
    // test2: A-B+C*D*E/F-G -> AB-CD*E*F/+G-
    int p = 0;
    scanf("%s", cal);
    for (int i = 0; i < strlen(cal); i++)
    {
        char op = cal[i];
        // printf("%c", op);
        // printf("cal[i]:%c ", cal[i]);
        if (op >= 'A' && op <= 'Z')
        {
            // printf("%c", op);
            postfix[p] = op;
            // printf("%c:%d\n", postfix[p], p);
            p++;
        }
        else if (op == '(')
        {
            push(op);
            // printf("op:%c, top:%d, stack[top]:%c\n", op, top, stack[top]);
        }
        else if (op == '*' || op == '/')
        {
            if (stack[top] == '*' || stack[top] == '/') // stack[top] == *, /
            {
                postfix[p] = pop();
                // printf("%c:%d\n", postfix[p], p);
                p++;
                push(op);
            }
            else if (IsEmpty() || stack[top] == '+' || stack[top] == '-'|| stack[top] == '(') // stack[top] == +, -, (
            {
                push(op);
            }
            // printf("op:%c, top:%d, stack[top]:%c\n", op, top, stack[top]);
        }
        else if (op == '+' || op == '-')
        {
            while (!IsEmpty() && stack[top] != '(') // stack[top] == +, -, *, /
            {
                postfix[p] = pop();
                // printf("%c:%d\n", postfix[p], p);
                p++;
            }
            push(op); // when stack[top] == '(' or empty
            // printf("op:%c, top:%d, stack[top]:%c\n", op, top, stack[top]);
        }
        else if (op == ')')
        {
            while (stack[top] != '(')
            {
                postfix[p] = pop();
                // printf("%c:%d\n", postfix[p], p);
                p++;
                // printf("op:%c, top:%d, stack[top]:%c\n", op, top, stack[top]);
            }
            pop(); // discard '('
            // printf("pop , top:%d, stack[top]:%c\n", top, stack[top]);

            while (!IsEmpty() && stack[top] != '(') // 把剩下的都 pop 掉，除非又遇到另一個括號
            {
                postfix[p] = pop();
                // printf("%c:%d\n", postfix[p], p);
                p++;
                // printf("op:%c, top:%d, stack[top]:%c\n", op, top, stack[top]);
            }
        }
    }
    while (!IsEmpty()) // 沒有字母代輸入之後，把 stack 中的所有東西 pop 出來
    {
        postfix[p] = pop();
        // printf("here\n");
        // printf("%c:%d\n", postfix[p], p);
        p++;
    }

    for (int i = 0; i < strlen(cal); i++)
    {
        printf("%c", postfix[i]);
    }
}