/**
 * @file expressions.h
 * 
 * @brief
 * @author Patrik Sehnoutek, xsehno01
 * @author Dovhalenko Dmytro, xdovha00
 */
#include "scanner.h"
#include "symtable.h"
#include "expressions_stack.h"

#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_

#define TABLE_SIZE 9 

typedef struct sData{
    
    bool isError;
    int errorValue;
    Token *token;
    Tframe_list *list;
    
    int indexType;
    int arrayType[20];
    bool checkDataType;


} Data_t;



typedef enum 
{
    SHIFT,  // <
    EQUAL,  // = 
    REDUC,  // >
    EMPTY   // ERROR
} TableItem; 

int rozpoznani_znaku(char*znak);
int vstupni_znak(Token* token);
int zasobnikovy_znak(Stack *s);
void do_shift(Stack*s,Token*token,int vstup,TNode *rootPtr);
void do_equal(Stack*s);
int kontrola_typu(Stack *s);
int do_reduc(Stack *s);
Token *exp_analysator(Data_t *data);

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
    E -> E // E
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