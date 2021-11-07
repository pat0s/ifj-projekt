/**
 * @file expressions.h
 * 
 * @brief
 * @author Patrik Sehnoutek, xsehno01
 * @author Dovhalenko Dmytro, xdovha00
 */
#include "scanner.h"
#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_

#define TABLE_SIZE 10 


typedef enum 
{
    SHIFT,  // <
    EQUAL,  // = 
    REDUC,  // >
    EMPTY   // ERROR
} TableItem; 

int vstupni_znak(Token* token);
int zasobnikovy_znak(Stack *s);
Token *exp_analysator(Token*token);

// Rules
/*
    E -> string
    E -> number
    E -> int
    E -> id
    E -> E + E
    E -> E - E
    E -> E * E
    E -> E / E
    E -> E > E
    E -> E < E
    E -> E >= E
    E -> E <= E
    E -> E ~= E
    E -> E == E
    E -> (E)
    E -> E..E
    E -> #E
*/

#endif

/* End of header file expressions.h */