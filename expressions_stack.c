/**
 * @file expressions_stack.c
 * 
 * @brief
 * @author Dovhalenko Dmytro, xdovha00
 */

#include "expressions_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_stack(Stack *s){
    s->top=NULL;
}

void push(Stack *s, char *new_data, char* new_type){
    SElement * new_element = (SElement *)malloc(sizeof(SElement));
    if(new_element ==NULL){
        //Error;
    }
    else{
        strcpy(new_element->data,new_data);
        strcpy(new_element->type,new_type);
        new_element->next_element=s->top;
        s->top=new_element;
    }
}

void pop(Stack *s){
    if(s->top!=NULL){
        SElement* tmp=s->top;
        s->top=tmp->next_element;
        free(tmp);
    }
}

void change_top_type(Stack *s,char*new_type){
    if(s->top!=NULL){
        strcpy(s->top->type,new_type);
    }
}

char* top(Stack *s){
    return s->top->data;
}

char* top_type(Stack *s){
    return s->top->type;
}

char* top1(Stack *s){
    if(s->top!=NULL){
        if(s->top->next_element!=NULL){
            SElement * tmp = s->top->next_element;
            return tmp->data;
        }
    }
    return NULL;
}

char* top1_type(Stack *s){
    if(s->top->next_element!=NULL){
        SElement * tmp = s->top->next_element;
        return tmp->type;
    }
    return NULL;
}

bool is_empty(Stack *s){
    return(s->top==NULL);
}

void destroy(Stack *s){
    while (s->top!=NULL){
        pop(s);
    }
    free(s);
}