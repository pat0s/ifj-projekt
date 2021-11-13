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
    char type [7];
    struct stackElement *next_element;
}SElement;

typedef struct stack{
    SElement *top;
}Stack;

void init_stack(Stack *s);
void push(Stack *s,char *data, char*type);
void pop(Stack *s);
char* top(Stack *s);
char* top_type(Stack *s);
void change_top_type(Stack *s,char*new_type);
char* top1(Stack *s);
char* top1_type(Stack *s);
bool is_empty(Stack *s);
void destroy(Stack *s);