/**
 * @file expressions_stack.h
 * 
 * @brief
 * @author Dovhalenko Dmytro, xdovha00
 */

#include <stdbool.h>

typedef struct stackElement
{   
    char data [12];
    struct stackElement *nextElement;
}SElement;

typedef struct stack{
    SElement *top;
}Stack;

void init_stack(Stack *s);
void push(Stack *s,char *data);
void pop(Stack *s);
char* top(Stack *s);
char* top1(Stack *s);
bool is_empty(Stack *s);