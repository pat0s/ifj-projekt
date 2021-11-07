#include "expressions_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_stack(Stack *s){
    s->top=NULL;
}

void push(Stack *s, char *newData){
    SElement * newElement = (SElement *)malloc(sizeof(SElement));
    if(newElement ==NULL){
        //Error;
    }
    else{
        strcpy(newElement->data,newData);
        newElement->nextElement=s->top;
        s->top=newElement;
    }
}

void pop(Stack *s){
    if(s->top!=NULL){
        SElement* tmp=s->top;
        s->top=tmp->nextElement;
        free(tmp);
    }
}

char* top(Stack *s){
    return s->top->data;
}

char* top1(Stack *s){
    if(s->top->nextElement!=NULL){
        SElement * tmp = s->top->nextElement;
        return tmp->data;
    }
    return NULL;
}

bool is_empty(Stack *s){
    return(s->top==NULL);
}